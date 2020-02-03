import makePriortyOrderedListOfOpenIndecis, {makeListOfSurroundingCells} from './makeListOfPrioIndecis';

describe('makeListOfSurroundingCells()', function () {
  test('works for thiese testcases', () => {
    // note: not compleate testing, but i have no reason for thinking it would fail
    const tests = [
      { // not touching any edge
        board: [
          0,  0,  0,  0,  0,
          0,  2,  0,  0,  0,
          0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,
          0,  0,  0,  0,  0 ],
        expectedResult: [
           0,  1,  2, -1, -1,
           5, -1,  7, -1, -1,
          10, 11, 12, -1, -1,
          -1, -1, -1, -1, -1,
          -1, -1, -1, -1, -1 ]
      },
      { // touching top
        board: [
          0,  2,  0,  0,  0,
          0,  2,  0,  0,  0,
          0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,
          0,  0,  0,  0,  0 ],
        expectedResult: [
           0, -1,  2, -1, -1,
           5, -1,  7, -1, -1,
          10, 11, 12, -1, -1,
          -1, -1, -1, -1, -1,
          -1, -1, -1, -1, -1 ]
      },
      { // touching right
        board: [
          0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,
          0,  0,  0,  1,  1,
          0,  0,  0,  0,  0,
          0,  0,  0,  0,  0 ],
        expectedResult: [
          -1, -1, -1, -1, -1,
          -1, -1,  7,  8,  9,
          -1, -1, 12, -1, -1,
          -1, -1, 17, 18, 19,
          -1, -1, -1, -1, -1 ]
      }
    ];

    tests.forEach(test => expect(makeListOfSurroundingCells(test.board, 5))
      .toEqual(test.expectedResult));
  });
});

describe('makePriortyOrderedListOfOpenIndecis()', function () {
  test('can pick the position closest to center first', () => {
    const tests = [{
        board: [
          0,  0,  0,  0,  0,  0,
            0,  2,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  //  idx: 12, 13, *14, 15, ..
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0 ],
        expectedFirstValue: 14
      },
      {
        board: [
          0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  2,  0,
          0,  0,  0,  0,  0,  0,  //  idx: 12, 13, 14, *15, ..
          0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0 ],
        expectedFirstValue: 15
      },
      {
        board: [
          0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  
          0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0, //  idx: 24, *25, 26, ..
          1,  0,  0,  0,  0,  0 ],
        expectedFirstValue: 25
      },
    ]
    const rowOf5 = 6, maxResuls = 2;
    tests.forEach(test => expect(makePriortyOrderedListOfOpenIndecis(test.board, rowOf5, maxResuls)[0])
      .toEqual(test.expectedFirstValue));
  });
});

describe('makePriortyOrderedListOfOpenIndecis()', function () {
  test('can select the given number of free positions, if available', () => {
    const board = [
        0,  0,  0,  0,  0,  0,
        0,  2,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  //  idx: 12, 13, *14, 15, ..
        0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0 ];
    const rowOf5 = 6
    const numberOfPositions = 5;
    const ordredPositions = makePriortyOrderedListOfOpenIndecis(board, rowOf5, numberOfPositions);
    expect(ordredPositions.length).toEqual(numberOfPositions);
  });
  test('when parameter3, size: -1 will give every surrouning poss', () => {
    const board = [
        0,  0,  0,  0,  0,  0,  // *  *  *  0
        0,  2,  0,  0,  0,  0,  // *  2  *  0
        0,  0,  0,  0,  0,  0,  // *  *  *  0
        0,  0,  0,  0,  0,  0,  // 0  0  0  0
        0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0 ];
    const rowOf5 = 6
    const ordredPositions = makePriortyOrderedListOfOpenIndecis(board, rowOf5, -1);
    expect(ordredPositions.length).toEqual(8); // 8 positions around that 2 on map
  });
});