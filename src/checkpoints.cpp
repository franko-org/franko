// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2013-2014 The Franko developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

#include <stdint.h>

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double SIGCHECK_VERIFICATION_FACTOR = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64_t nTimeLastCheckpoint;
        int64_t nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    bool fEnabled = true;

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
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
        ( 216802, uint256("0x0c946c4bdb51a240a103059f69112f301995e3a293044d3a4eff8d4c95cb0a5e1"))
        ( 219638, uint256("0x035fcdaff88c5b989895047f2be66948618feec9ceefaa947341c4f58c55d9362"))
        ( 323288, uint256("0x089a2340f2715a4bede40ce7f095a8d841df7a18c46f76c21c312b31cee2c7a8d"))
        ( 402360, uint256("0x014a96abb528216321b91ac3f29918b60e9292d5cada7a047fcaeb6177c93fbe6"))
        ( 402376, uint256("0x041f33e89e8369d88e1a516a4860fb0c1b4b8b5037f28388a9fd062e4966258f6"))
		( 472665, uint256("0x07b532f4e96384b2de42f73803572ae5a2bfbecf19462cf2c9f754e7421498ba0"))
		( 605904, uint256("0x97a0618b8971a7627eb30f3346245af28fe43e32af117b915132b8c0efb1c1f9"))
		( 785863, uint256("0x9ea053de310cc64a14c9b48849f9ed1e5b5898b30696f3d935b40047feb2306b"))
		( 785950, uint256("0x1ea42eb64c0a5027549e58d2b532e4fe5da6c901b723fd2ae2d4b7263807e8da"))
		( 786082, uint256("0x980e5394dee86c2d12572cff87d74b260e2e37c2ef321118cf5a7b68f15188ea"))
		( 805345, uint256("0xa35e590108bb87970c748ea4f39bc700fc1adf3e0cfea28317f6f7236beeebb3"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1403212414, // * UNIX timestamp of last checkpoint block
        941685,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        5000     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (     0, uint256("0x"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1369685559,
        37581,
        300
    };

    static MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("3d2160a3b5dc4a9d62e7e66a295f70313ac808440ef7400d6c0772171ce973a5"))
        ;
    static const CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

    const CCheckpointData &Checkpoints() {
        if (Params().NetworkID() == CChainParams::TESTNET)
            return dataTestnet;
        else if (Params().NetworkID() == CChainParams::MAIN)
            return data;
        else
            return dataRegtest;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!fEnabled)
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex, bool fSigchecks) {
        if (pindex==NULL)
            return 0.0;

        int64_t nNow = time(NULL);

        double fSigcheckVerificationFactor = fSigchecks ? SIGCHECK_VERIFICATION_FACTOR : 1.0;
        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkpoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!fEnabled)
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!fEnabled)
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
