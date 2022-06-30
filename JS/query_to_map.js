function convertQueryToMap(query) {
    return query.split("&").reduce((map, params) => {
        let [props, value] = params.split("=");

        if (!value) return map;

        props = props.split(".");
        let lastProp = props.pop();
        let deepestObject = props.reduce((obj, key) => {
            return obj[key] || (obj[key] = {});
        }, map);

        deepestObject[lastProp] = decodeURIComponent(value);

        return map;
    }, {});
}