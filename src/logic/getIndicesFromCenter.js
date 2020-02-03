const cashedResult = {}


/**
 * will produce a list of Indecis reprecenting positions around center of a square
 * A square with row 4 :
 * | 0   1   2   3  |
 * | 4   5   6   7  |
 * | 8   9   10  11 |
 * | 12  13  14  15 |
 * will hava a list looking something like: [5, 6, 9, 10, 1, 2, 7, ..., 0, 3, 12, 15 ] since
 * 5, 6, 9 10 is closest to center.
 * The list does not have to be perfect, its only used for selecting cells from the inside out.
 * @param {number} boxRow 
 */
function produceListOfIndecisFromCenter(boxRow) {
  const tempArray = [];
  const centerPos = (boxRow - 1) / 2.0;
  let index = 0;
  for (let i = 0; i < boxRow; i++) {
    for (let j = 0; j < boxRow; j++, index++) {
      tempArray.push({
        distSquared: (i - centerPos) * (i - centerPos) + (j - centerPos) * (j - centerPos),
        order: index
      });
    }
  }
  const reoreder = tempArray.sort( (a, b) => {
    return a.distSquared < b.distSquared ? -1 : a.distSquared > b.distSquared ? 1 : 0;
  });
  return reoreder.map(e => e.order);
}

export default function getIndicesFromCenter(boxRow) {
  if ( !cashedResult[boxRow] ) {
    cashedResult[boxRow] = produceListOfIndecisFromCenter(boxRow);
  }
  return cashedResult[boxRow];
} 