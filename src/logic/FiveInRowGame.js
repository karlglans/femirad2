import GameBoard, {debugCount} from './GameBoard';
import MinmaxSearch from './MinMaxSearch';
import { fiveInRow } from './ranking';

export default class FiveInRowGame {
  constructor(row, maxSearchDepth) {
    this.gameBoard = new GameBoard(row);
    this.row = row;
    this.ply = 0;
    this.maxSearchDepth = 5; // standard: 5
    this.move = [];
    this.tempClick = 0;
    this.gameIsOver = false;

    this.initDebugGameSituation(0); // 4 is still bad
  }

  initDebugGameSituation(situation) {
    if (situation === 1) {
      this.gameBoard.setCell(7 * 16 + 6, 2);
      this.gameBoard.setCell(7 * 16 + 7, 1);
      this.gameBoard.setCell(8 * 16 + 6, 1);
      this.gameBoard.setCell(8 * 16 + 7, 2);
      this.gameBoard.setCell(8 * 16 + 8, 2);
      this.gameBoard.setCell(9 * 16 + 8, 2);
      this.gameBoard.setCell(6 * 16 + 8, 1);
      this.gameBoard.setCell(6 * 16 + 5, 1);
      this.gameBoard.setCell(7 * 16 + 9, 1);
      this.ply = 7; 
    } else if (situation === 2) {
      this.gameBoard.setCell(7 * 16 + 6, 2);
      this.gameBoard.setCell(7 * 16 + 7, 1);
      this.gameBoard.setCell(8 * 16 + 6, 2);
      this.gameBoard.setCell(8 * 16 + 7, 2);
      this.gameBoard.setCell(8 * 16 + 5, 2);
      this.gameBoard.setCell(8 * 16 + 4, 1);
      this.gameBoard.setCell(8 * 16 + 8, 2);
      this.gameBoard.setCell(8 * 16 + 9, 1);
      this.gameBoard.setCell(7 * 16 + 9, 1);
      this.gameBoard.setCell(6 * 16 + 9, 1);
      this.gameBoard.setCell(6 * 16 + 8, 1);
      this.gameBoard.setCell(6 * 16 + 6, 1);
      this.gameBoard.setCell(5 * 16 + 9, 2);
      this.gameBoard.setCell(6 * 16 + 10, 2);
      this.gameBoard.setCell(8 * 16 + 10, 2);
      this.gameBoard.setCell(5 * 16 + 7, 1);

      // this.gameBoard.setCell(9 * 16 + 3, 2);
      
      // this.gameBoard.setCell(117, 1); --> 72
      // this.gameBoard.setCell(72, 1); --> 147

      console.log('should have been red', 7 * 16 + 5);
      console.log('should have been blye', 72);
      console.log('should have been red', 9 * 16 + 3);

      // ply is 16
      // problem: should have selected 117 but are selecting 103
      // both best child nodes are 103
      // rest of child nodes have value -1

      // this.gameBoard.setCell(120, 1);
 
      this.ply = 16; 
    } else if (situation === 3) {
      this.gameBoard.setCell(4 * 16 + 3, 1);
      this.gameBoard.setCell(3 * 16 + 4, 2);
      this.gameBoard.setCell(3 * 16 + 3, 1);
      this.gameBoard.setCell(2 * 16 + 4, 2);
      this.gameBoard.setCell(2 * 16 + 3, 1);
      this.ply = 5; 
    } else if (situation === 4) {
      // this is a sure loss. And the ago is performing unnecessarily bad
      // It should go for 89? would prolong the game
      this.gameBoard.setCell(7 * 16 + 6, 2);
      this.gameBoard.setCell(7 * 16 + 7, 1);
      this.gameBoard.setCell(8 * 16 + 6, 1);
      this.gameBoard.setCell(8 * 16 + 7, 2);
      this.gameBoard.setCell(8 * 16 + 8, 2);
      this.gameBoard.setCell(9 * 16 + 8, 2);
      this.gameBoard.setCell(6 * 16 + 8, 1);
      this.gameBoard.setCell(6 * 16 + 5, 1);
      this.gameBoard.setCell(7 * 16 + 9, 1);
      this.gameBoard.setCell(10 * 16 + 9, 2);
      this.gameBoard.setCell(11 * 16 + 10, 1);
      this.gameBoard.setCell(9 * 16 + 5, 2);
      this.gameBoard.setCell(6 * 16 + 9, 1);
      console.log('blue', 5 * 16 + 9);
      this.ply = 11; // 11
    } 
  }

  /**
   * Will make the a move for the active team.
   */
  doNextMove() {
    const {gameBoard, ply, maxSearchDepth, gameIsOver} = this;
    return new Promise( (resolve, reject) => {
      setTimeout(() => {
        const teamToAct = (ply % 2) + 1;

        if (gameIsOver) reject();
        const t1 = performance.now();
        
        const search = new MinmaxSearch(gameBoard, ply, maxSearchDepth);
        const move = search.search();
        if (move != null && !gameIsOver) {
          this.gameBoard = gameBoard.applyMove(move, teamToAct);
          this.evaluateWinningMove(move);
          this.ply = ply + 1;
        }
        resolve(move && move.cellIdx);

        const t2 = performance.now();
        console.log('move done', (t2 - t1) * 0.001, debugCount() );
      }, 0);
    });
  }

  reset() {
    this.gameBoard = new GameBoard(this.row);
    this.ply = 0;
    this.move = [];
    this.gameIsOver = false;
  }

  evaluateWinningMove(move) {
    const {ply} = this;
    // note: a win is given value: fiveInRow - ply by search algo 
    if (move.value >= (fiveInRow - ply - 1)) {
      this.gameIsOver = true;
    }
  }

  currentPlayer() {
    return (this.ply % 2) + 1;
  }
  isGameOver() {
    return this.gameIsOver;
  }
  getGameState() {
    return this.gameBoard;
  }
  getGameBoard() {
    return this.gameBoard.getBoard();
  }
  setCell(cellIdx) {
    const {gameBoard} = this;
    gameBoard.setCell(cellIdx, this.currentPlayer());
    if (gameBoard.evaluateWin(this.currentPlayer()) >= fiveInRow) {
      this.gameIsOver = true;
    }
    this.ply += 1;
  }
};
