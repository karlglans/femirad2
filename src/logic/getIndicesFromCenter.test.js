import getIndicesFromCenter from './getIndicesFromCenter';

describe('getIndicesFromCenter(row)', function () {
  test('should give an array with size sqr of row', () => {
    const indices = getIndicesFromCenter(5);
    expect(indices.length).toBe(5 * 5);
  });
  test('will have the four innermost cells listed first', () => {
    // | 0   1   2   3  |
    // | 4   5*  6*  7  |
    // | 8   9*  10* 11 |
    // | 12  13  14  15 |
    const indicesFrom4x4 = getIndicesFromCenter(4);
    const firstFourIndices = indicesFrom4x4.splice(0, 4);
    expect(firstFourIndices).toEqual([5, 6, 9, 10]); // in an 4x4 matrix
  });
});