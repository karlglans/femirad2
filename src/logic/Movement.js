

export default class Movement {
  constructor(cellIdx) {
    this.cellIdx = cellIdx;
  }

  getCellId() {
    return this.cellIdx;
  }
};