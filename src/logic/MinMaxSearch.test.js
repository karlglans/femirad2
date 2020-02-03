import MinMaxSearch from "./MinMaxSearch";
import GameBoard from "./GameBoard";

// put xdescribe to remove these tests
xdescribe('some expensive search tests', function () {
  const row = 8, teamOne = 1, teamTwo = 2, searchDepth = 5;
  const gameBoard = new GameBoard(row);
  const gameBoardExpected = new GameBoard(row);
  //   test.only('move 1: block opponent', () => {
  //     gameBoard.setBoard([
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 1, 2, 0, 0, 0, 0,
  //       0, 0, 1, 2, 0, 0, 0, 0,
  //       0, 0, 1, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //     ]);
  //     gameBoardExpected.setBoard([
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 2, 0, 0, 0, 0, 0,
  //       0, 0, 1, 2, 0, 0, 0, 0,
  //       0, 0, 1, 2, 0, 0, 0, 0,
  //       0, 0, 1, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //     ]);
  //     gameBoardError.setBoard([
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 2, 1, 2, 0, 0, 0, 0,
  //       0, 0, 1, 2, 0, 0, 0, 0,
  //       0, 0, 1, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //       0, 0, 0, 0, 0, 0, 0, 0,
  //     ]);
  //     const ply = 5; // means player 2 should act
  //     const minmax = new MinMaxSearch(gameBoard, ply, 5);
  //     const nextBoard = gameBoard.applyMove(minmax.search(), teamTwo);
  //     nextBoard.print();
  //     expect(nextBoard.getBoard()).toStrictEqual(gameBoardError.getBoard());
  // });
  test('move 2: team 1 will compeate 4-cell-line', () => {
    gameBoard.setBoard([
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
    ]);
    gameBoardExpected.setBoard([
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
    ]);
    const ply = 6; // means player 1 should act
    const minmax = new MinMaxSearch(gameBoard, ply, searchDepth);
    const nextBoard = gameBoard.applyMove(minmax.search(), teamOne);
    expect(nextBoard.getBoard()).toStrictEqual(gameBoardExpected.getBoard());
  });
  test('move 2: team 2 will compleate 4-cell-line', () => {
    gameBoard.setBoard([
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
    ]);
    gameBoardExpected.setBoard([
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 1, 0, 2, 0, 0, 0, 0,
      0, 0, 1, 2, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
    ]);
    const ply = 7; // means player 2 should act
    const minmax = new MinMaxSearch(gameBoard, ply, searchDepth);
    const nextBoard = gameBoard.applyMove(minmax.search(), teamTwo);
    expect(nextBoard.getBoard()).toStrictEqual(gameBoardExpected.getBoard());
  });
});