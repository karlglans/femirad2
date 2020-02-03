import GamestateNode from './GamestateNode';
import { fiveInRow } from './ranking';

const max_children = 40; // s0: 4 10: 18 35
const highValue = fiveInRow * 100;

/**
 * 
 * @param {GamestateNode} gamestateNode
 * @param {integer} ply round number
 * @param {integer} maxPly number bigger then ply
 * @param {1 or 2} team acting team for whole search
 * @param {integer} ply0 ply for start of the search
 * @param {bool} shouldMax
 * @param {number} alpha
 * @param {number} beta
 */
export function minMax(gamestateNode, ply, maxPly, team, ply0, shouldMax, alpha, beta) {
  const plyTeam = (ply % 2) + 1; // 1 or 2. Acting team for this turn
  const prevTeam = plyTeam === 1 ? 2 : 1;
  gamestateNode.applyMoveToGameboard(prevTeam);

  // stop searching deeper if this node is a win
  if (gamestateNode.checkWin(prevTeam)) {
    // will reward shortest path to win by subtracting ply
    const reward = prevTeam === team ? fiveInRow - ply : -fiveInRow;
    gamestateNode.value = reward;
    return reward;
  }

  if (ply === maxPly) {
    return gamestateNode.staticEvaluation(prevTeam);
  }
  
  // optimization: decrease number of children depending on depth. note: (ply0 - ply) is negative
  let nChildren = Math.max(max_children + (ply0 - ply) * 2, 2);

  const doEverySurroundingCell = ply0 > 0 && ply === ply0;
  const children = gamestateNode.generateChildren(nChildren, doEverySurroundingCell);
  const len = children.length;
  let value;
  if (shouldMax) {
    for (let i = 0; i < len; i++) {
      value = minMax(children[i], ply + 1, maxPly, team, ply0, !shouldMax, alpha, beta);
      // children[i].v = children[i].move.cellIdx; // debugging
      alpha = Math.max(value, alpha);
      if (beta <= alpha) {
        break;
      }
    }
  } else {
    for (let i = 0; i < len; i++) {
      value = minMax(children[i], ply + 1, maxPly, team, ply0, !shouldMax, alpha, beta);
      // children[i].v = children[i].move.cellIdx; // debugging
      beta = Math.min(value, beta);
      if (beta <= alpha) {
        break;
      }
    }
  }
  gamestateNode.releaseBoard(); // to save some memory
  gamestateNode.sortChildren(!shouldMax); // warning (why not plyTeam?)
  gamestateNode.value = gamestateNode.getValueFromFirstChild();

  return gamestateNode.value;
}

export default class MinMaxSearch {
  constructor(gameBoard, ply, maxSeachDepth) {
    this.gameBoard = gameBoard;
    this.ply = ply;
    this.maxPly = ply + maxSeachDepth;
    // 1 or 2. Acting team for this turn. Relevant since we can play on both teams
    this.team = (ply % 2) + 1; 
  }

  search() {
    const { gameBoard, ply, maxPly, team } = this;
    const ply0 = ply;
    // move: null, since the move is already integreated into the current gameboard
    const node0 = new GamestateNode(gameBoard, null, ply0);
    // debugger;
    const value = minMax(node0, ply, maxPly, team, ply0, true, -highValue, highValue);
    // console.log(node0);
    const move = node0.getBestMove();
    move.value = value;
    return move; 
  }
}