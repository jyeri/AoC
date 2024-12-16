class PriorityQueue {
    constructor(comparator = (a, b) => a[0] - b[0]) { // Min-heap by default
        this.heap = [];
        this.comparator = comparator;
    }

    push(val) {
        this.heap.push(val);
        this._siftUp();
    }

    pop() {
        const top = this.heap[0];
        const end = this.heap.pop();
        if (this.heap.length > 0) {
            this.heap[0] = end;
            this._siftDown();
        }
        return top;
    }

    _siftUp() {
        let idx = this.heap.length - 1;
        const elem = this.heap[idx];
        while (idx > 0) {
            const parentIdx = Math.floor((idx - 1) / 2);
            const parent = this.heap[parentIdx];
            if (this.comparator(elem, parent) >= 0) break;
            this.heap[idx] = parent;
            this.heap[parentIdx] = elem;
            idx = parentIdx;
        }
    }

    _siftDown() {
        let idx = 0;
        const length = this.heap.length;
        const elem = this.heap[idx];
        while (true) {
            const leftIdx = 2 * idx + 1;
            const rightIdx = 2 * idx + 2;
            let swapIdx = null;

            if (leftIdx < length && this.comparator(this.heap[leftIdx], elem) < 0) {
                swapIdx = leftIdx;
            }
            if (
                rightIdx < length &&
                this.comparator(this.heap[rightIdx], (swapIdx === null ? elem : this.heap[leftIdx])) < 0
            ) {
                swapIdx = rightIdx;
            }
            if (swapIdx === null) break;
            this.heap[idx] = this.heap[swapIdx];
            this.heap[swapIdx] = elem;
            idx = swapIdx;
        }
    }

    size() {
        return this.heap.length;
    }
}

module.exports = PriorityQueue;