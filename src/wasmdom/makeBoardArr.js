
const gameSize = 16 * 16;
let boarBufferPtr = -1;

export default function makeBoardArr(size) {
  return new Int8Array(gameSize)
}

export function allocBoardBuffer() {
  console.log('allocBoardBuffer');
  boarBufferPtr = window.Module._malloc(gameSize);
  window.Module._memset(boarBufferPtr, 0, gameSize);
}

function freeBoardBuffer() {
  console.log('freeBoardBuffer');
  window.Module._free(boarBufferPtr);
  boarBufferPtr = -1;
}

export function startNewGame() {
  console.log('startNewGame');
}

export function releaseWasm() {
  console.log('releaseWasm called');
  window.Module.ccall('releaseApp', null, [], []);
  freeBoardBuffer();
}

/**
 * @param {i32} cellIdx
 * @return {bool} gameIsOver
 */
export function markEmptyCell(cellIdx) {
  if (boarBufferPtr !==  -1) {
    const retV = window.Module.ccall('markEmptyCell', 'number', ['*', 'i32'], [boarBufferPtr, cellIdx]);
    console.log('retV', retV, cellIdx);
    return retV === 0;
  } 
  return false; 
}

/**
 * @return {bool} gameIsOver
 */
export function doNextMove() {
  const searchDepth = 11; // odd numbers [3, 5, 7, 9]
  const t1 = performance.now();
  const result = window.Module.ccall('doNextMove', 'i32', ['i32', '*'], [searchDepth, boarBufferPtr]);
  const t2 = performance.now()
  console.log('move done', (t2 - t1) * 0.001);
  return result;
}

export function copyBoardBuffer() {
  if (boarBufferPtr !==  -1) {
    const newArr = new Int8Array(window.Module.HEAP8.buffer, boarBufferPtr, gameSize);
    return newArr;
  }
  return [];
}