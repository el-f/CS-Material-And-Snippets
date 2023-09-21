/*
  task description:
  remove words from message until it is longer than K characters
  if message is truncated, add "..." to the end, only if there is enough space for it
  if message is not truncated, return message as is
  if no word was left in the message, return "..."
*/

function solution(message, K) {
  if (message.length <= K) return message;

  for (let r = message.length - 1; r >= 0; r--) {
    if (message[r] === " " && r + 4 <= K) {
      return message.slice(0, r) + " ...";
    }
  }

  return "..."
}

const main = () => {
  const inputs = [
    [["And now here is my secret", 15],
      "And now ..."],

    [["There is an animal with four legs", 15],
      "There is an ..."],

    [["super dog", 4],
      "..."],

    [["how are you", 20],
      "how are you"],
  ]


  for (const [input, expected] of inputs) {
    const [message, K] = input;
    const result = solution(message, K);
    const pass = result === expected;
    if (pass) {
      console.log(`PASS`);
    } else {
      console.log(`FAIL: ${result} !== ${expected}`);
    }
  }
}
main();