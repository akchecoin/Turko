// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Akchecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    // Will add checkpoints after the first block is mined.

    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            ( 0, uint256("0x19225ae90d538561217b5949e98ca4964ac91af39090d1a4407c892293e4f44f"))
            ( 10, uint256("0xb98fe58aa04ca9a5a216c0bd01d952e0fff16e702d0fb512f748f201b9be26fb"))
            ( 100, uint256("0x56b00c7d17fd10680dfafa0617f26af75f6c2b0c11aafa9cf1b6704de2766f72"))
            ( 1000, uint256("0x076d62aef68a8330e5f927cdbc23d58ac1e2838877936512aa16487f098d35ca"))
            ( 5000, uint256("0x5b7fc427fa913510186e034e1415bdf987d37f4674c2f2fd0b492836fc58de0d"))
            ( 10000, uint256("0xd4bf99505611f97b6cf6f273a79c21c1b21b03238b06396e2e9a02f83c13d01c"))
            ( 27000, uint256("0x397e50d20f9a21f274b8787fa66ca1ebc208a1b7e5bc3a9a0e352350bd42e125"))
            ( 27650, uint256("0xb2a25b57648bf10a81dcc3b23fb758bceb6f652d121bd44b2f3c7da3fd0f0cef"))
            ( 29040, uint256("0x34b4dbe94b3e1bc0f6b199ee722a9fbbb52315ae53dd37cbc949fbc84aa3c6fe"))
            ( 48080, uint256("0x08f789323bf5d116575c5749fa617696f88d0179faac534647abb5065abbaddf"))
            ( 60000, uint256("0x046ca133f715de3f8d83965487002c9cc1cebe4bb0fc10a1155fc9a6d2767293b"))
            ( 70000, uint256("0x01ad0aa03e8888cef8381aeea5ca679602bbb32e8245e9cd36abce77cda936bfb"))
            ( 80000, uint256("0x03a508431391d8203d4dd8fde8ffc529c26923cc8da9f2e64342441bb7afa940c"))
            ( 90000, uint256("0x08571865fb72beddf95872cbe3490aeb2b7558c7810b0a4aef9d581e249ef9d98"))
            ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;

        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
