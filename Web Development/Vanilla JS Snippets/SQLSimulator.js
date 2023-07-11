// 545434090294935e7d0010ab

const _ = require('lodash');

const cartesianProduct = (...xs) => {
    if (xs.length === 1) return xs[0];
    return _.flatMap(xs[0], (value) => _.map(cartesianProduct(...xs.slice(1)), (product) => _.concat(value, product)));
};

const recursiveGroupBy = (xs, fns) => {
    if (fns.length === 0) return xs;
    return _.toPairs(_.mapValues(_.groupBy(xs, fns[0]), (x) => recursiveGroupBy(x, fns.slice(1))));
}

const fixNumberStrings = obj => JSON.parse(JSON.stringify(obj).replace(/"(-?\d+)"/g, '$1'));

function query() {
    const whereFns = [];
    const havingFns = [];
    let selectFn, fromFn, groupByFns, orderByFn;
    this.select = (fn = x => x) => {
        if (selectFn) throw new Error('Duplicate SELECT');
        selectFn = fn;
        return this;
    };
    this.from = (head, ...tail) => {
        if (fromFn) throw new Error('Duplicate FROM');
        fromFn = () => cartesianProduct(head, ...tail);
        return this;
    };
    this.where = (...fns) => {
        whereFns.push((x) => _.some(fns, (fn) => fn(x)));
        return this;
    };
    this.groupBy = (...fns) => {
        if (groupByFns) throw new Error('Duplicate GROUPBY');
        groupByFns = fns;
        return this;
    };
    this.having = (fn) => {
        havingFns.push(fn);
        return this;
    };
    this.orderBy = (fn) => {
        if (orderByFn) throw new Error('Duplicate ORDERBY');
        orderByFn = fn;
        return this;
    };
    this.execute = () => {
        let result = fromFn && fromFn() || [];
        if (whereFns.length)  result = _.filter(result, _.overEvery(whereFns));
        if (groupByFns)       result = recursiveGroupBy(result, groupByFns);
        if (havingFns.length) result = _.filter(result, _.overEvery(havingFns));
        if (orderByFn)        result = _.clone(result).sort(orderByFn);
        return fixNumberStrings(_.map(result, selectFn)); // fix numbers converted to string by _.groupBy
    };
    return this;
}