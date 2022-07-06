const _48bitMAC = "^[0-9a-fA-F]{2}(\\.[0-9a-fA-F]{2}){5}$|^[0-9a-fA-F]{2}(:[0-9a-fA-F]{2}){5}$|^[0-9a-fA-F]{2}(-[0-9a-fA-F]{2}){5}$";
const _64bitMAC = "^[0-9a-fA-F]{2}(\\.[0-9a-fA-F]{2}){7}$|^[0-9a-fA-F]{2}(:[0-9a-fA-F]{2}){7}$|^[0-9a-fA-F]{2}(-[0-9a-fA-F]{2}){7}$";
const _48bitMAC_3Chunks = "^[0-9a-fA-F]{4}(\\.[0-9a-fA-F]{4}){2}$";

const pattern = _48bitMAC + "|" + _64bitMAC + "|" + _48bitMAC_3Chunks, flags = "";