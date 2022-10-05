(function (api, condition) {
    if (api.env.platform === "android" || api.env.platform === "ios") {
        return;
    }

    condition.enable();
});
