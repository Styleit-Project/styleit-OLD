// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Styleit developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include <assert.h>
#include <boost/assign/list_of.hpp>
using namespace std;
using namespace boost::assign;
struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};
#include "chainparamsseeds.h"
/**
 * Main network
 */
//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions


static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000000438ce468bba8384721f59b2bde0f772171764081d14b795b4167766ddc"))
    (100, uint256("0x0000070f65bb6e49d5a3f23ec825b6281f25cbe6364b405003c5c7979c9250f1"))
    (1500, uint256("0x00000ebd8fad302b738c232a5f4b5ac28df59ec7999f3902bf40ca92c44e649a"))
    (3000, uint256("0x5faf4afb57a97b2a9200bf62f23eec03fc05952285d5b2a45ff550a938f7621f"))
    (9000, uint256("0xab68ab7bb530fffd96949fbf563ac06f7c7f945422b42596fa571a726d17a5b7"))
    (25000, uint256("0xecfcd755edfd88d9888c169a699ad396e5ada9a5b7a8beddfa5248c7a56415f6"))
    ;


static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1602007039, // * UNIX timestamp of last checkpoint block
    52785,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1440         // * estimated number of transactions per day after checkpoint
};
static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x000000438ce468bba8384721f59b2bde0f772171764081d14b795b4167766ddc"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1599386459,
    0,
    200};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x45467ae1649f21f24b66e796e710415db3c81390c264c4dc2f8591e33f73af3c"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1599386459,
    0,
    100};
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0x23;
        pchMessageStart[3] = 0xc5;
        vAlertPubKey = ParseHex("042c63003ede070e5fc8811ce36d8625b555d81926fa459dabbec2514d62e0c79718038f115f5ba098948d44313b5e48db499113dc586c4df2c1681c79b5c7ed20");
        nDefaultPort = 15140;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 1 * 60;
        nLastPOWBlock = 2000;
        nMaturity = 150;
        nMaxMoneyOut = 1000000000 * COIN;
        nModifierUpdateBlock = 1;
		
        const char* pszTimestamp = "Styleit utility Coin for our online payment.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04f7516e9d49d2143331da208ce80daee98f992c6508b787e294883504718b6af5777724a9e4c6da7f45b6e08d8c252f8fbfa667025ccfd49e2ea7d333695f5527") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1599386459;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 714153;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000000438ce468bba8384721f59b2bde0f772171764081d14b795b4167766ddc"));
        assert(genesis.hashMerkleRoot == uint256("0xc7a48c56132d08cac0568858da6510dbdd300d90820ec390f7aa80bad168dfda"));

        vSeeds.push_back(CDNSSeedData("styleit.me", "node1.styleit.me"));
        vSeeds.push_back(CDNSSeedData("styleit.me", "node2.styleit.me"));
	    vSeeds.push_back(CDNSSeedData("styleit.me", "node3.styleit.me"));
	    vSeeds.push_back(CDNSSeedData("styleit.me", "node4.styleit.me"));
        vSeeds.push_back(CDNSSeedData("styleit.me", "node5.styleit.me"));
	    vSeeds.push_back(CDNSSeedData("styleit.me", "node6.styleit.me"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 10);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 135);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x0a)(0x00).convert_to_container<std::vector<unsigned char> >();
		
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
		
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
		
        nPoolMaxTransactions = 3;
        strSporkKey = "04f37b92460c61aba36c2aaed23405cec599a71899eae20c395db2d7a4328f758a58acbb9c3d4ae4a1c14eb802c816af782d14f5888052a3a87abce8b2bde93e24";
        strObfuscationPoolDummyAddress = "CQ4fj33mJBaxMWcxjAz9GP8pJ7vZfQRxju";
        nStartMasternodePayments = 1599566400; //Thursday, February 20, 2020 7:00:00 PM GMT +00
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x2c;
        pchMessageStart[1] = 0xca;
        pchMessageStart[2] = 0x34;
        pchMessageStart[3] = 0xac;
        vAlertPubKey = ParseHex("04d1d4df7ac6e3719b0c981789d5d33e311cb32dbe21e2ddc165206e8ce4cabd9cd1781cb778be25c323e309ce71b3a8446eff0f8c282a05a86b3cb44c1e533fd8");
        nDefaultPort = 15040;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Styleit: 1 day
        nTargetSpacing = 1 * 60;  // Styleit: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMaxMoneyOut = 200000000 * COIN;  // Limited Maximum money to 200,000,000
        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1599386459;
        genesis.nNonce = 714153;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000000438ce468bba8384721f59b2bde0f772171764081d14b795b4167766ddc"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("styleit.me", "node7.styleit.me"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet styleit addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet styleit script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet styleit BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet styleit BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet styleit BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
		
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
		
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
		
        nPoolMaxTransactions = 2;
        strSporkKey = "04f37b92460c61aba36c2aaed23405cec599a71899eae20c395db2d7a4328f758a58acbb9c3d4ae4a1c14eb802c816af782d14f5888052a3a87abce8b2bde93e24";
        strObfuscationPoolDummyAddress = "CQ4fj33mJBaxMWcxjAz9GP8pJ7vZfQRxju";
        nStartMasternodePayments = 1599566400; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;
/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xec;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0xab;
        pchMessageStart[3] = 0xd1;
        nSubsidyHalvingInterval = 210000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Styleit: 1 day
        nTargetSpacing = 1 * 60;        // Styleit: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1599386459;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x45467ae1649f21f24b66e796e710415db3c81390c264c4dc2f8591e33f73af3c"));

        nDefaultPort = 47006;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
		
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;
/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 17312;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;
static CChainParams* pCurrentParams = 0;
CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}
const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}
CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}
void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}
