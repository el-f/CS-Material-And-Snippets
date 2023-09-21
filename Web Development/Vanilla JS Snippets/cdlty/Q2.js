/*
  task description:
  given a list of customers who are waiting for their packages, and each customer's number is the number of the package they are waiting for
  return the maximum number of packages that were on the shelf at the same time
  a package is placed on the shelf if it has not been picked up yet.
  packages are arriving in order (1, 2, 3, 4, 5, ...) and customers can pick up their packages in any order.
  if a customer arrives and their package is not on the shelf, they will wait until it arrives, while other packages are placed on the shelf.
*/

function solution(wantedPackages) {
  let currentArrivingPackage = 1;
  let maxSetSize = 0;
  const shelf = new Set();

  wantedPackages.forEach((wantedPackage) => {
    if (shelf.has(wantedPackage)) {
      shelf.delete(wantedPackage);
    } else {
      while (currentArrivingPackage != wantedPackage) {
        shelf.add(currentArrivingPackage);
        currentArrivingPackage++;
        maxSetSize = Math.max(maxSetSize, shelf.size);
      }
      currentArrivingPackage++;
    }
  });

  return maxSetSize;
}

const main = () => {
  const inputs = [
    [[3, 2, 4, 5, 1], 2],
    [[1, 2, 3, 4, 5], 0],
    [[3, 2, 7, 5, 4, 1, 6], 4]
  ];

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