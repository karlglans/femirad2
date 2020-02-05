import React, {useState, useEffect} from 'react';
import './App.css';

import Grid from './components/Grid';
import ControlPanel from './components/ControlPanel';

import FiveInRow from './logic/FiveInRowGame';
import makeBoardArr, {allocBoardBuffer, copyBoardBuffer, markEmptyCell, releaseWasm, doNextMove} from './wasmdom/makeBoardArr';

const row = 16;
const game = new FiveInRow(row);

function App() {
  const [gameBoard, setGameBoard] = useState(game.getGameBoard());
  const [isAllowingNextStep, setIsAllowingNextStep] = useState(true);
  const [currentPlayer, setCurrentPlayer] = useState(1);
  const [lastChangedCellIdx, setLastChangedCellIdx] = useState(-1);
  const [gameOver, setGameOver] = useState(false);
  const [boardArr, setBoardArr] = useState(makeBoardArr(16*16));
  const [startedStep, setStartedStep] = useState(0);
  const [finishedStep, setFinishedStep] = useState(0);

  function handleStep() {
    if (startedStep === finishedStep && isAllowingNextStep) {
      setIsAllowingNextStep(false);
      setStartedStep(startedStep + 1);
    }
  }

  useEffect( () => {
    if (startedStep > 0 && startedStep !== finishedStep) {
      function doStepWithTimout() {
        setFinishedStep(startedStep);
        setTimeout(() => {
          const change = doNextMove();
          const gameIsOver = change === -1;
          setIsAllowingNextStep(true);
          setCurrentPlayer(currentPlayer === 1? 2: 1);
          setGameOver(gameIsOver);
          setBoardArr(copyBoardBuffer());
          if (!gameIsOver) {
            setLastChangedCellIdx(change);
          }
        }, 0);
      };

      doStepWithTimout();
    }
  }, [startedStep, finishedStep, currentPlayer, isAllowingNextStep]);

  useEffect( () => {
    setTimeout(() => allocBoardBuffer(), 100);
    return () => releaseWasm();
  }, []);

  function handleClickCell(cellIdx) {
    if (isAllowingNextStep && !gameOver) {
      const gameIsOver = markEmptyCell(cellIdx);
      setCurrentPlayer(currentPlayer === 1? 2: 1); // maybe data from game instead
      setGameOver(gameIsOver);
      setBoardArr(copyBoardBuffer());
      setFinishedStep(startedStep + 1);
      setStartedStep(startedStep + 1);
    }
  }

  function handleRestart() {
    if (isAllowingNextStep) {
      game.reset();
      setLastChangedCellIdx(-1);
      setGameOver(game.isGameOver());
      setCurrentPlayer(game.currentPlayer());
      setGameBoard(game.getGameBoard());
    }
  }
  
  return (
    <div className="App" style={{display: 'flex', justifyContent: 'center', height: 'calc(100VH)', alignItems: 'center', backgroundColor: '#ebebeb' }}>
      <div style={{ position: 'relative', height: 600, width: 600 }}>
        <Grid
          row = {row}
          gameBoard = {gameBoard}
          handleClickCell = {handleClickCell}
          lastChangedCellIdx = {lastChangedCellIdx}
          boardArr = {boardArr}
        />
        <ControlPanel
          gameOver={gameOver}
          handleStep={handleStep}
          handleRestart={handleRestart}
          isAllowingNextStep={isAllowingNextStep}
          currentPlayer={currentPlayer}
        />
      </div>
    </div>
  );
}

export default App;
