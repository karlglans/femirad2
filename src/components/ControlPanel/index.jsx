
import React, {useState, useEffect} from 'react';

const ControlPanel = props => {
  const [allowInput, setAllowInput] = useState(false);
  const setButtonText = props.isAllowingNextStep ? 'step' : 'wait';
  const nextPlayer = 1 + props.currentPlayer % 2;
  const currentPlayer = props.gameOver ? nextPlayer : props.currentPlayer;
  const bgColor = props.isAllowingNextStep ?
    currentPlayer === 1? 'red': 'blue' : 
    currentPlayer === 1? 'red': 'blue';

  useEffect( () => {
    // to prevent a second click to get stored when main component stuck on heavy job
    if(!props.isAllowingNextStep) setAllowInput(false);
    setTimeout(() => {
      setAllowInput(props.isAllowingNextStep);
    }, 100)
  }, [props.isAllowingNextStep]);
  
  return (
    <div className={!allowInput ? 'animate-flicker' : null}
      style={{ position:'absolute', height: 100, width: 100, right: -110, top: 0, backgroundColor: bgColor }}
    >
      {!props.gameOver && ( <button style={{marginTop: 20, cursor: 'pointer' }} disabled={!allowInput} 
        onClick={props.handleStep}> 
        {setButtonText} </button>)}
      {props.gameOver && (<p style={{color:'white'}}>Game Over</p>)}
      {props.gameOver && ( <button style={{marginTop: 5}} onClick={props.handleRestart}> 
        restart </button>)}
    </div>
  );
};

export default ControlPanel;