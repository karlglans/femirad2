import getIndicesFromCenter from './getIndicesFromCenter';

/**
 *   example of row 4 :
 *       --- u --->
 *    |   0  1  2  3
 *    v   4  5  6  7
 *    |   8  9  10 11
 *    V   12 13 14 15
 *    
 * 
 *  board[]:                       surroundingCells[]:
 *  0* 0* 0* 0* 0  0  0  0         0  1  2  3  -1 -1 -1 -1
 *  0* 1  1  0* 0  0  0  0         8  -1 -1 11 -1 -1 -1 -1
 *  0* 0* 1  0* 0  0  0  0         16 17 18 19 -1 -1 -1 -1
 *  0  0* 0* 0* 0  0  0  0   ==>   -1 25 26 27 -1 -1 -1 -1
 *  0  0  0  0  0  0  0  0         -1 -1 -1 -1 -1 -1 -1 -1
 *  0  0  0  0  0  0  0  0         -1 -1 -1 -1 -1 -1 -1 -1
 *  0  0  0  0  0  0  0* 0*        48 -1 -1 -1 -1 -1 54 55
 *  0  0  0  0  0  0  0* 2         -1 -1 -1 -1 -1 -1 62 -1
 *                                  
 */

export function makeListOfSurroundingCells(boardArr, row) {
  const result = [], isNotASurroundingCell = -1;
  let idx = 0;
  // iterates over each position decides if this position is neighbouring some taken cells
  for(let v = 0; v < row; v++) {
    for(let u = 0; u < row; u++, idx++) {
      if (boardArr[idx] !== 0) {
        result[idx] = isNotASurroundingCell;
      } else {

        // checking directions up/down/left/right
        if (u !== 0 && boardArr[idx - 1] !== 0) {
          result[idx] = idx;
        } else if (u !== (row -1) && boardArr[idx + 1] !== 0) {
          result[idx] = idx;
        } else if (v !== 0 && boardArr[idx - row] !== 0) {
          result[idx] = idx;
        } else if (v !== (row -1) && boardArr[idx + row] !== 0) {
          result[idx] = idx;
        
        // diagonals
        } else if (u !== 0 && v !== 0 && boardArr[idx - row - 1] !== 0) {
          result[idx] = idx;
        } else if (u !== (row -1) && v !== 0 && boardArr[idx - row + 1] !== 0) {
          result[idx] = idx;
        } else if (u !== 0 && v !== (row -1) && boardArr[idx + row - 1] !== 0) {
          result[idx] = idx;
        } else if (u !== (row -1) && v !== (row -1) && boardArr[idx + row + 1] !== 0) {
          result[idx] = idx;
    
        } else {
          result[idx] = isNotASurroundingCell;
        }
      }
    }  
  }
  return result;
}

/**
 * Will return an array of possible (free) positions. 
 * When searching new positions, then positions will be taken from this array.
 * Positions around exisiting structures on the game board and positions in the center will be
 * considered more valuable. More valuable positions will end up first.
 * @param {number} maxSize maximum size of result array or -1 for every surrounding cell
 */
export default function makePriortyOrderedListOfOpenIndecis(boardArr, row, maxSize) {
  const fromMiddleAndOut = getIndicesFromCenter(row); // every possible position, just in diff order
  const openPositionsAroundStructures = makeListOfSurroundingCells(boardArr, row);
  const orderedFreePositions = [];
  const otherOpenPositions = [];
  let count = 0;
  fromMiddleAndOut.forEach(cellIdx => {
    if (count < maxSize || maxSize === -1) {
      if (openPositionsAroundStructures[cellIdx] === cellIdx) {
        orderedFreePositions.push(cellIdx);
        if (maxSize !== -1) count++;
      } else if (boardArr[cellIdx] === 0) {
        otherOpenPositions.push(cellIdx);
      }
    }
  });
  if (maxSize === -1) {
    // should return every openPositionsAroundStructures
    return orderedFreePositions;
  }
  // we are still looking for more open positions
  otherOpenPositions.forEach(cellIdx => {
    if (count < maxSize) {
      orderedFreePositions.push(cellIdx);
      count++;
    }
  });
  // we havent found enogh free positions, just return what we have
  return orderedFreePositions;
}
