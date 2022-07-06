function Counter(array) {
    const count = {};
    array.forEach(val => count[val] = (count[val] || 0) + 1);
    return count;
}

_ = require('lodash');

CounterV2 = _.countBy

const testArr = [1, 2, 3, 4, 5, 6, 7, 8, 2, 3, 3,]
console.log(CounterV2(testArr))
console.log(Counter(testArr))


function dominator(array) {
    const count = _.countBy(array);
    if (new Set(Object.values(count)).size === 1) return -1;
    return _.maxBy(Object.keys(count), key => count[key]);
}