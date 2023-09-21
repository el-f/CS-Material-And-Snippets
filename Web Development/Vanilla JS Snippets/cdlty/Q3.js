/*
  task description:
  given a list of blocks, each block has a height
  return the maximum length of a subarray that forms a 'saddle' shape
  a saddle shape is a subarray such that each element towards the middle of the array is smaller
  than or equal to the element next to it which closer to one of the ends of the array than it is.
*/

function solution(blocks) {
  const n = blocks.length;
  const geToTheLeft = new Array(n).fill(0);
  const geToTheRight = new Array(n).fill(0);

  for (let i = 1; i < n; i++) {
    if (blocks[i] <= blocks[i - 1]) {
      geToTheLeft[i] = geToTheLeft[i - 1] + 1;
    }
  }


  for (let i = n - 2; i >= 0; i--) {
    if (blocks[i] <= blocks[i + 1]) {
      geToTheRight[i] = geToTheRight[i + 1] + 1;
    }
  }

  let max = 0;
  for (let i = 0; i < n; i++) {
    max = Math.max(max, geToTheLeft[i] + geToTheRight[i] + 1);
  }

  return max;
}

const main = () => {
  const inputs = [
    [[2, 6, 8, 5], /* expected: */ 3],
    [[1, 5, 5, 2, 6], /* expected: */ 4],
    [[1, 1, 1], /* expected: */ 3],
    [[1, 2, 3, 4, 5, 6, 7], /* expected: */ 7],
    [[1, 2, 1, 2, 1, 2, 1], /* expected: */ 3],
    [[1, 1], /* expected: */ 2],
    [[1], /* expected: */ 1],
  ]

  for (const [input, expected] of inputs) {
    const result = solution(input);
    const pass = result === expected;
    if (pass) {
      console.log(`PASS`);
    } else {
      console.log(`FAIL: ${result} !== ${expected}`);
    }
  }

}
main();