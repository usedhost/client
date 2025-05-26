#pragma once

#include <cstdint>
#include <string>

namespace bedrock {
    class NetworkIdentifier {
    public:
        enum class Type : std::uint32_t {
            RakNet = 0,
            Address = 1,
            Address6 = 2,
            NetherNet = 3,
            Invalid = 4,
        };

        std::uint64_t nether_net_id;
        /*
        RakNet::RakNetGUID guid;       // +8
        union {                        //
            sockaddr_storage sa_stor;  //
            sockaddr_in6 addr6;        //
            sockaddr_in addr4;         //
        } sock; */
        Type type;

        [[nodiscard]] std::string getAddress() const;
        [[nodiscard]] std::uint16_t getPort() const;
        [[nodiscard]] Type getType() const;
        bool operator==(const NetworkIdentifier& other) const;
        bool operator!=(const NetworkIdentifier& other) const;
        [[nodiscard]] bool equalsTypeData(const NetworkIdentifier& other) const;
    };

    struct NetworkIdentifierWithSubId {
        NetworkIdentifier id;
        SubClientId sub_client_id;
    };
}