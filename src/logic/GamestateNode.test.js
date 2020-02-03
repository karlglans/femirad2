import GamestateNode from './GamestateNode';

describe('GamestateNode:sortChildren(team, plyTeam)', function () {
  const parentNode = new GamestateNode(null, null, 0);
  const someNode1 = new GamestateNode(null, null, 0);
  const someNode2 = new GamestateNode(null, null, 0);
  const someNode3 = new GamestateNode(null, null, 0);
  test('when team == plyTeam, will sort children by lowest values', () => {
    const lowest = 4;
    someNode1.value = 11;
    someNode2.value = lowest;
    someNode3.value = 12;
    parentNode.children = [someNode1, someNode2, someNode3];
    // act
    const team = 2, plyTeam = 2;
    parentNode.sortChildren(team, plyTeam);
    expect(parentNode.children[0].value).toBe(lowest);
  });
  test('when team != plyTeam, will sort children by highest values', () => {
    const highest = 199;
    someNode1.value = 11;
    someNode2.value = highest;
    someNode3.value = 12;
    parentNode.children = [someNode1, someNode2, someNode3];
    // act
    const team = 0, plyTeam = 1;
    parentNode.sortChildren(team, plyTeam);
    expect(parentNode.children[0].value).toBe(highest);
  });
});