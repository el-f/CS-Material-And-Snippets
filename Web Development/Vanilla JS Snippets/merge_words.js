function condense(string) {
    return string
        .replace(/(\w*?)(\w*)(?= \2\w*)/g, '$1')
        .replace(/ /g, '')
}