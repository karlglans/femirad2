import React from 'react';

const ControlPanel = props => {
  const setButtonText = props.isAllowingNextStep ? 'step' : 'wait';
  const nextPlayer = 1 + props.currentPlayer % 2;
  const currentPlayer = props.gameOver ? nextPlayer : props.currentPlayer;
  const bgColor = props.isAllowingNextStep ?
    currentPlayer === 1? 'red': 'blue' : 
    currentPlayer === 1? 'red': 'blue';
  return (
    <div className={!props.isAllowingNextStep ? 'animate-flicker' : null}
      style={{ position:'absolute', height: 100, width: 100, right: -110, top: 0, backgroundColor: bgColor }}
    >
      {!props.gameOver && ( <button style={{marginTop: 20}} disabled={!props.isAllowingNextStep} onClick={props.handleStep}> 
        {setButtonText} </button>)}
      {props.gameOver && (<p style={{color:'white'}}>Game Over</p>)}
      {props.gameOver && ( <button style={{marginTop: 5}} onClick={props.handleRestart}> 
        restart </button>)}
    </div>
  );
};

export default ControlPanel;