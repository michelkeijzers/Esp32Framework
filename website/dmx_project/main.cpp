#include "httplib.h"
#include "json.hpp"
#include <vector>
#include <string>

using json = nlohmann::json;

int main() {
    httplib::Server svr;

    // Example preset data (names and activation status)
    std::vector<std::pair<std::string, bool>> presets = {
        {"Warm White", true},
        {"Cool Blue", false},
        {"Party Mode", false},
        {"Sunset", false},
        {"Stage Wash", false},
        {"Strobe", false},
        {"Fade", false},
        {"Rainbow", false},
        {"UV", false},
        {"Spotlight", false},
        {"Chase", false},
        {"Pulse", false},
        {"Fire", false},
        {"Ice", false},
        {"Relax", false},
        {"Focus", false},
        {"Energy", false},
        {"Ambient", false},
        {"Accent", false},
        {"Custom Scene", false}
    };

    svr.Get("/api/presets", [&](const httplib::Request&, httplib::Response& res) {
        json j = json::array();
        for (const auto& p : presets) {
            j.push_back({{"name", p.first}, {"active", p.second}});
        }
        res.set_content(j.dump(), "application/json");
    });

    svr.listen("0.0.0.0", 8080);
}
