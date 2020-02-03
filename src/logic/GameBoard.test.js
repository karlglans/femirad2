import GameBoard from './GameBoard';
import { open2cells, semiOpen2cells, open3cells, semiOpen3cells, open4row,
  semiOpen4row, fiveInRow } from './ranking';
import Move from './Movement';

// create a smaller board (8x8) just for testing
const row = 8, team = 1, teamOne = 1;
const gameBoard = new GameBoard(row);
const gameBoard12x12 = new GameBoard(12);


describe('gameBoard:evaluate()', () => {
  describe('line:2', () => {
    // testing 2x2 more then the other 3x3,
    describe('horizontal', () => {
      describe('open', () => {
        test('combinations', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 1, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 1, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 1, 0, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(4 * open2cells);
        });
        // ta bort
        test('open problem 1', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 1, 1, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 1, 1, 0, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 1, 1, 0, 
          ]); 
          expect(gameBoard.evaluate(team)).toBe(3 * open2cells);
        });
        // ta bort
        test('open problem 2', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 0, 1, 1, 0, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 1, 1, 0, 
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 1, 1, 0, 
          ]); 
          expect(gameBoard.evaluate(team)).toBe(3 * open2cells);
        });
      });
      describe('semi-open', () => {
        test('closed by edges', () => {
          gameBoard.setBoard([
            1, 1, 0, 0, 0, 0, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 1, 1,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(6 * semiOpen2cells);
        });
        test('closed by opponent', () => {
          gameBoard.setBoard([
            2, 1, 1, 0, 0, 1, 1, 2,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 1, 2, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 2, 1, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            2, 1, 1, 0, 0, 1, 1, 2,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(6 * semiOpen2cells);
        });
      });
    });
    describe('vertical', () => {
      describe('open', () => {
        test('simple case', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 0, 0, 
            1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 1, 
            0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 
          ]); 
          expect(gameBoard.evaluate(team)).toEqual(4 * open2cells);
        });
      });
      describe('semi-open', () => {
        describe('closed by opponent', () => {
          test('above', () => {
            gameBoard.setBoard([
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 
              0, 0, 0, 0, 0, 0, 0, 0,
              2, 0, 0, 0, 0, 0, 0, 2,
              1, 0, 0, 0, 0, 0, 0, 1,
              1, 0, 0, 0, 0, 0, 0, 1,
              0, 0, 0, 0, 0, 0, 0, 0, 
            ]); 
            expect(gameBoard.evaluate(team)).toBe(2 * semiOpen2cells);
          });
          test('below', () => {
            gameBoard.setBoard([
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              1, 0, 0, 0, 0, 0, 0, 1, 
              1, 0, 0, 0, 0, 0, 0, 1,
              2, 0, 0, 0, 0, 0, 0, 2,
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 
            ]); 
            expect(gameBoard.evaluate(team)).toBe(2 * semiOpen2cells);
          });
        });
        describe('closed by edge', () => {
          test('top', () => {
            gameBoard.setBoard([
              1, 0, 0, 1, 0, 0, 0, 1,
              1, 0, 0, 1, 0, 0, 0, 1,
              0, 0, 0, 0, 0, 0, 0, 0, 
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 
            ]); 
            expect(gameBoard.evaluate(team)).toBe(3 * semiOpen2cells);
          });
          test('bottom', () => {
            gameBoard.setBoard([
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              1, 0, 0, 0, 1, 0, 0, 1,
              1, 0, 0, 0, 1, 0, 0, 1, 
            ]); 
            expect(gameBoard.evaluate(team)).toBe(3 * semiOpen2cells);
          });
        });
      })
    });
    describe('rising', () => {
      describe('open', () => {
        test('combinations', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(1 * open2cells);
        });
      });
      test('by edge. testset1', () => {
        gameBoard.setBoard([
          0, 0, 0, 0, 0, 0, 0, 1,
          0, 1, 0, 0, 0, 0, 1, 0,
          1, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 1,
          0, 1, 0, 0, 0, 0, 1, 0,
          1, 0, 0, 0, 0, 0, 0, 0,
        ]); 
        expect(gameBoard.evaluate(team)).toBe(4 * semiOpen2cells);
      });
      test('by edge. testset2', () => {
        gameBoard.setBoard([
          0, 0, 1, 0, 0, 0, 0, 0,
          0, 1, 0, 0, 0, 0, 0, 1,
          0, 0, 0, 0, 0, 0, 1, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 1, 0, 0, 0, 1, 0,
          0, 1, 0, 0, 0, 1, 0, 0,
        ]); 
        expect(gameBoard.evaluate(team)).toBe(4 * semiOpen2cells);
      });
      test('by edge. testset3', () => {
        gameBoard.setBoard([
          0, 0, 0, 0, 0, 0, 1, 0,
          0, 0, 0, 0, 0, 1, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 1, 0, 0, 0, 0, 0, 0,
          1, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
        ]); 
        expect(gameBoard.evaluate(team)).toBe(2 * semiOpen2cells);
      });
    });
    describe('falling', () => {
      describe('open', () => {
        test('combinations', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0,
            0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0,
            0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(3 * open2cells);
        });
      });
      describe('closed', () => {
        test('by edge. testset1', () => {
          gameBoard.setBoard([
            1, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 1,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 1,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(4 * semiOpen2cells);
        });
        test('by edge. testset2', () => {
          gameBoard.setBoard([
            0, 0, 1, 0, 0, 1, 0, 0,
            1, 0, 0, 1, 0, 0, 1, 0,
            0, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 1,
            0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(6 * semiOpen2cells);
        });
        test('by opponent. testset1', () => {
          gameBoard.setBoard([
            2, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 2,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0,
            0, 0, 0, 2, 0, 0, 0, 2,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(4 * semiOpen2cells);
        });
        test('by opponent. testset2', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 2, 0, 0, 0,
            0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0,
            0, 0, 0, 2, 0, 0, 0, 0,
            2, 0, 0, 0, 2, 0, 0, 0,
            0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(4 * semiOpen2cells);
        });
      });
    });
  });
  describe('line:3', () => {
    describe('horizontal', () => {
      test('open variations', () => {
        gameBoard.setBoard([
          0, 0, 0, 0, 1, 1, 1, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,  
          0, 1, 1, 1, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 1, 1, 1, 0, 0, 0,
        ]); 
        expect(gameBoard.evaluate(team)).toBe(3 * open3cells);
      });
      test('semi-open variations', () => {
        gameBoard.setBoard([
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 2, 1, 1, 1, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          1, 1, 1, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 1, 1, 1,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 1, 1, 1, 2, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
        ]); 
        expect(gameBoard.evaluate(team)).toBe(4 * semiOpen3cells);
      });
    });
    describe('vertical', () => {
      test('open variations', () => {
        gameBoard.setBoard([
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          1, 0, 0, 1, 0, 0, 0, 1,
          1, 0, 0, 1, 0, 0, 0, 1,
          1, 0, 0, 1, 0, 0, 0, 1,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
        ]); 
        expect(gameBoard.evaluate(team)).toBe(3 * open3cells);
      });
      test('semi-open variations', () => {
        gameBoard.setBoard([
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          2, 0, 0, 0, 0, 0, 0, 0,
          1, 0, 0, 1, 0, 0, 0, 0,
          1, 0, 0, 1, 0, 0, 0, 0,
          1, 0, 0, 1, 0, 0, 0, 1,
          0, 0, 0, 2, 0, 0, 0, 1,
          0, 0, 0, 0, 0, 0, 0, 1,
        ]); 
        expect(gameBoard.evaluate(team)).toBe(3 * semiOpen3cells);
      });
    });
    describe('falling', () => {
      describe('open', () => {
        test('combinations', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 1, 0, 0, 0,
            0, 0, 1, 0, 0, 1, 0, 0,
            0, 0, 0, 1, 0, 0, 1, 0,
            0, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(3 * open3cells);
        });
      });
      describe('semi-open', () => {
        test('close by edge', () => {
          gameBoard.setBoard([
            1, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 1,
            0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(3 * semiOpen3cells);
        });
        test('close by opponent', () => {
          gameBoard.setBoard([
            0, 0, 0, 2, 0, 0, 0, 0,
            0, 1, 0, 0, 1, 0, 0, 0,
            0, 0, 1, 0, 0, 1, 0, 0,
            2, 0, 0, 1, 0, 0, 1, 0,
            0, 1, 0, 0, 2, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(3 * semiOpen3cells);
        });
      });
    });
    describe('rising', () => {
      describe('open', () => {
        test('combinations', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 1, 0,
            0, 0, 1, 0, 0, 1, 0, 0,
            0, 1, 0, 0, 1, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(3 * open3cells);
        });
      });
      describe('semi-open', () => {
        test('close by edge', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 0, 0, 0, 1,
            0, 0, 0, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0,
            0, 1, 0, 0, 0, 1, 0, 0,
            1, 0, 0, 0, 1, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(3 * semiOpen3cells);
        });
        test('close by opponent', () => {
          gameBoard.setBoard([
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 1, 0,
            0, 0, 1, 0, 0, 1, 0, 0,
            0, 1, 0, 0, 1, 0, 0, 0,
            2, 0, 0, 2, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0,
            0, 0, 0, 2, 0, 0, 0, 0,
          ]); 
          expect(gameBoard.evaluate(team)).toBe(3 * semiOpen3cells);
        });
      });

    });
  });
  describe('line:4', () => {
    test('open orthogonal variations', () => {
      gameBoard.setBoard([
        0, 0, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,  
        0, 0, 0, 1, 0, 0, 0, 1,
        0, 0, 0, 1, 0, 0, 0, 1,
        0, 0, 0, 1, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 1, 1, 1, 1, 0, 0,
      ]); 
      expect(gameBoard.evaluate(team)).toBe(open4row);
    });
    test('open vertical variations', () => {
      gameBoard.setBoard([
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,  
        0, 1, 0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 1, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
      ]); 
      expect(gameBoard.evaluate(team)).toBe(open4row);
    });
    // test('open cossing', () => {
    //   gameBoard.setBoard([
    //     0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 1, 0, 0, 0, 0,  
    //     0, 0, 1, 1, 1, 1, 0, 0,
    //     0, 0, 0, 1, 0, 0, 0, 0,
    //     0, 0, 0, 1, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0, 0,
    //   ]); 
    //   expect(gameBoard.evaluate(team)).toBe(2 * open4row);
    // });
    test('semi-open variations', () => {
      gameBoard.setBoard([
        0, 0, 0, 0, 1, 1, 1, 1,
        0, 0, 0, 2, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,  
        0, 0, 0, 1, 0, 0, 0, 1,
        0, 0, 0, 1, 0, 0, 0, 1,
        0, 0, 0, 1, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 1, 1, 1, 1, 2, 2,
      ]); 
      expect(gameBoard.evaluate(team)).toBe(4 * semiOpen4row);
    });
  });
});

describe('gameBoard:setBoard()', function () {
  test('will reverse line order', () => {
    const smallGameBoard = new GameBoard(4);
    smallGameBoard.setBoard([
      41, 42, 43, 44, 
      31, 32, 33, 34, 
      21, 22, 23, 24,
      11, 12, 13, 14,
    ]);
    expect(smallGameBoard.getBoard()).toEqual(
      [ 11, 12, 13, 14,  21, 22, 23, 24,  31, 32, 33, 34,  41, 42, 43, 44, ]);
  });
});

describe('gameBoard:generateMoves()', function () {
  test('can return empty array if no possible moves', () => {
    gameBoard.setBoard([
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
    ]);
    expect(gameBoard.generateMoves().length).toBe(0);
  });
  test('can return an array of possible moves closest to center', () => {
    gameBoard.setBoard([
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 1, // rejected pos, since we only asking for 2
        0, 0, 1, 1, 1, 1, 1, 1, // zeros in pos 40, 41
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
    ]);
    // note pos 41 is closer to middle and will therefore be selected first
    expect(gameBoard.generateMoves(2)).toEqual([new Move(41), new Move(40)]);
  });
  describe('gameBoard:applyMove()', function () {
    describe('when no move argument', function () {
      test('will create new instance', () => {
        const newBoard = gameBoard.applyMove();
        expect(newBoard).not.toBe(gameBoard);
      });
      test('will have same board-values', () => {
        gameBoard.setBoard([
          1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1,
          2, 2, 2, 2, 2, 2, 2, 2,
          2, 2, 2, 2, 2, 2, 2, 2,
          2, 2, 2, 2, 2, 2, 2, 2,
          2, 2, 2, 2, 2, 2, 2, 2,
        ]);
        const newBoard = gameBoard.applyMove();
        const oldBoardArr = gameBoard.getBoard();
        expect(newBoard.getBoard()).toEqual(oldBoardArr);
      });
    });
    describe('when getting a move-argument', function () {
      test('should alter the new just the new gameboard', () => {
        gameBoard.setBoard([
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
        ]);
        const someTeam = 2, somePositon = 11;
        const newBoard = gameBoard.applyMove(new Move(somePositon), someTeam);
        expect(newBoard.getBoard()[somePositon]).toBe(someTeam);
        expect(gameBoard.getBoard()[somePositon]).toBe(0);
      });
    });
  });
});

describe('gameBoard:evaluateWin()', () => {
  test('can detect horizontal line', () => {
    // three types: 1 open, 2 semi open (both types)
    gameBoard.setBoard([
      0, 0, 0, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 1, 1, 1, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 1, 0, 0, 0,
    ]);
    expect(gameBoard.evaluateWin(teamOne)).toEqual(3 * fiveInRow);
  });
  test('can detect vertical line', () => {
    // three types: 1 open, 2 semi open (both types)
    gameBoard.setBoard([
      0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 1, 0, 1,
      0, 1, 0, 0, 0, 1, 0, 1,
      0, 1, 0, 0, 0, 1, 0, 1,
      0, 1, 0, 0, 0, 1, 0, 0,
      0, 1, 0, 0, 0, 1, 0, 0,
      0, 1, 0, 0, 0, 0, 0, 0,
    ]);
    expect(gameBoard.evaluateWin(teamOne)).toEqual(3 * fiveInRow);
  });
  test('can detect multiple horizontal lines', () => {
    gameBoard12x12.setBoard([
      1, 1, 1, 1, 1, 0,  1, 1, 1, 1, 1, 0, // ex closed right
      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1,  1, 1, 1, 1, 0, 0,
      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,

      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 1,  0, 1, 1, 1, 1, 1, // ex closed left
      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,  0, 1, 1, 1, 1, 1,
    ]);
    expect(gameBoard12x12.evaluateWin(teamOne)).toEqual(6 * fiveInRow);
  });
  test('can detect horizontal vertical lines', () => {
    gameBoard12x12.setBoard([
      1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 0,

      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 1,
    ]);
    expect(gameBoard12x12.evaluateWin(teamOne)).toEqual(6 * fiveInRow);
  });
  test('can detect falling lines', () => {
    gameBoard12x12.setBoard([
      1, 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, // 0, 11
      0, 1, 0, 0, 0, 0,  0, 0, 1, 0, 0, 0, // 12
      0, 0, 1, 0, 0, 0,  0, 0, 0, 1, 0, 0, // 24
      0, 0, 0, 1, 0, 0,  0, 0, 0, 0, 1, 0, // 36
      0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 0, 1, // 48
      0, 0, 1, 0, 0, 0,  0, 0, 0, 0, 0, 0, // 60

      0, 0, 0, 1, 0, 0,  0, 0, 0, 0, 0, 0, // 72
      1, 0, 0, 0, 1, 0,  0, 1, 0, 0, 0, 0, // 84
      0, 1, 0, 0, 0, 1,  0, 0, 1, 0, 0, 0, // 96
      0, 0, 1, 0, 0, 0,  1, 0, 0, 1, 0, 0, // 108
      0, 0, 0, 1, 0, 0,  0, 0, 0, 0, 1, 0, // 120
      0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 0, 1, // 132, 143
    ]);
    expect(gameBoard12x12.evaluateWin(teamOne)).toEqual(5 * fiveInRow);
  });
  test('can detect falling line', () => {
    // four types: 1 open, 2 semi open (both types), and one closes both sides
    gameBoard.setBoard([
      0, 0, 0, 1, 0, 0, 0, 0,
      1, 0, 0, 0, 1, 0, 0, 0,
      0, 1, 1, 0, 0, 1, 0, 0,
      0, 1, 1, 1, 0, 0, 1, 0,
      0, 0, 1, 1, 1, 0, 0, 1,
      0, 0, 0, 1, 1, 1, 0, 0,
      0, 0, 0, 0, 1, 0, 1, 0,
      0, 0, 0, 0, 0, 1, 0, 0,
    ]);
    expect(gameBoard.evaluateWin(teamOne)).toEqual(4 * fiveInRow);
  });
  test('can detect rising lines in 12x13', () => {
    gameBoard12x12.setBoard([
      0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 1, // 0, 11
      0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 1, 0, // 12
      0, 0, 0, 1, 0, 0,  0, 0, 0, 1, 0, 0, // 24
      0, 0, 1, 0, 0, 0,  0, 0, 1, 0, 0, 0, // 36
      0, 1, 0, 0, 0, 0,  0, 1, 0, 0, 0, 1, // 48
      1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0, // 60

      0, 0, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, // 72
      0, 0, 0, 0, 1, 0,  0, 0, 1, 0, 0, 1, // 84
      0, 0, 0, 1, 0, 0,  0, 1, 0, 0, 1, 0, // 96
      0, 0, 1, 0, 0, 0,  0, 0, 0, 1, 0, 0, // 108
      0, 1, 0, 0, 0, 0,  0, 0, 1, 0, 0, 0, // 120
      1, 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, // 132, 143
    ]);
    expect(gameBoard12x12.evaluateWin(teamOne)).toEqual(5 * fiveInRow);
  });
  test('can detect rising lines in 8x8', () => {
    // four types: 1 open, 2 semi open (both types), and one closes both sides
    gameBoard.setBoard([
      0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 1, 0, 1, 0, 1,
      0, 0, 1, 0, 1, 0, 1, 0,
      0, 1, 0, 1, 0, 1, 1, 0,
      1, 0, 1, 0, 1, 1, 0, 0,
      0, 1, 0, 1, 1, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
    ]);
    expect(gameBoard.evaluateWin(teamOne)).toEqual(4 * fiveInRow);
  });
});
