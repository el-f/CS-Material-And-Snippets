
const LOCALE = 'he-IL';

const historyJsonPath = process.argv[2];
if (!historyJsonPath) {
  console.error('Please provide the history json path as an argument');
  process.exit(1);
}

const history = require(historyJsonPath);

/**
 * parse total amount string to number
 * @param {string} totalAmountShekel total amount string
 * @param {string} currencySymbol currency symbol to remove from the string
 * @returns {number} total amount as number
 */
const totalAmountToNumber = (totalAmountShekel, currencySymbol = '₪') => {
  const parsed = +(totalAmountShekel.replace(currencySymbol, ''));
  return isNaN(parsed) ? 0 : parsed;
}

const totalAmount = history.orders.reduce((acc, curr) => acc + totalAmountToNumber(curr.total_amount), 0);
const totalOrdersCount = history.orders.length;
const lastOrderDate = history.orders.at(0).payment_time_ts;
const firstOrderDate = history.orders.at(-1).payment_time_ts;
const mostExpensiveOrder = history.orders.reduce((acc, curr) => {
  return totalAmountToNumber(curr.total_amount) > totalAmountToNumber(acc.total_amount) ? curr : acc;
}, history.orders.at(0));
const cheapestOrder = history.orders
  .filter(order => totalAmountToNumber(order.total_amount) > 0)
  .reduce((acc, curr) => {
    return totalAmountToNumber(curr.total_amount) < totalAmountToNumber(acc.total_amount) ? curr : acc;
  }, history.orders.at(0));

const formatSummaryAsAsciiTable = () => {
  const table = [
    ['total orders', totalOrdersCount],
    ['sum of total orders', `${totalAmount} ₪`],
    ['first order date', new Date(firstOrderDate).toLocaleString(LOCALE)],
    ['last order date', new Date(lastOrderDate).toLocaleString(LOCALE)],
    ['most expensive order', `${mostExpensiveOrder.total_amount} ₪`],
    ['cheapest order', `${cheapestOrder.total_amount} ₪`],
  ];

  const maxLength = table.reduce((acc, curr) => Math.max(acc, curr[0].length), 0);
  table.unshift(['-'.repeat(maxLength), '-'.repeat(20)]);
  table.push(['-'.repeat(maxLength), '-'.repeat(20)]);

  return table.map(([key, value]) => `${key.padEnd(maxLength)} | ${value}`).join('\n');
}

console.log(`Wolt history summary:`);
console.log(formatSummaryAsAsciiTable());
