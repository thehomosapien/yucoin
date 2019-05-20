// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017 The YUCOIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
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
    (0, uint256("0x0000088e48539afb86bc6edee67e8c32f76368cb5d9b920be69b6a9ae1d87e15"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1557919770, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x000008ef772289b67f6801a278f7e0b98622b54aaf85ae9723fcc4748d62a834"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1557916759,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x2f8cb3e3acca6779d7fbe63a9d21d760a7a28f4fb793bdf12f2cefa4cda44867"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1557913159,
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
        pchMessageStart[0] = 0x59; // Y
        pchMessageStart[1] = 0x55; // U
        pchMessageStart[2] = 0x43; // C
        pchMessageStart[3] = 0x42; // B
        vAlertPubKey = ParseHex("04656afae3641b24dbfb2b4a8bae45d9f14a82939d70b6baa6425bdb2364d6f0c84e3e5d2887cf7cbaf6508b7d103f6df21de0a7965bdef9920675240af9aa94b1");
        nDefaultPort = 22220;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; // YUCOIN: 1 day
        nTargetSpacing = 1 * 60;  // YUCOIN: 1 minutes
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 45000000 * COIN;
		
		 

        /** Height or Time Based Activations **/
        nLastPOWBlock = 250;
        nModifierUpdateBlock = 1; // we use the version 2 for YUC

        const char* pszTimestamp = "Joe Lubin, Jimmy Song Strike $500K Crypto Bet on Ethereum’s Future";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04a1855446eb4dd3482c470681ceb2dfdd0865912bc34795acfe1584818614de8a4035b15e85718f1d132aaecffbb3e080acd50c52aa36ee3cdee0eff72edfd8e7") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1557919770;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 5878791;         
        hashGenesisBlock = genesis.GetHash();             

        assert(hashGenesisBlock == uint256("0x0000088e48539afb86bc6edee67e8c32f76368cb5d9b920be69b6a9ae1d87e15"));
        assert(genesis.hashMerkleRoot == uint256("0x9ef08e4a86a09c4a380ade8caa111d036b54edd43b28e56ff01aecc2b7512c71"));
        
        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("74.208.135.213", "74.208.135.213"));
        vSeeds.push_back(CDNSSeedData("108.175.14.64", "108.175.14.64"));
 
		


        // YUCOIN addresses start with 'Y'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 78);
        // YUCOIN script addresses start with '3'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 114);
        // YUCOIN private keys start with 'K'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 46);
        // YUCOIN BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x06)(0x84)(0xB5)(0x1A).convert_to_container<std::vector<unsigned char> >();
        // YUCOIN BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x05)(0x83)(0xAF)(0xE1).convert_to_container<std::vector<unsigned char> >();
        // YUCOIN BIP44 coin type is '222' (0x800000de)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x60)(0x00)(0x00)(0xdb).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04a1855446eb4dd3482c470681ceb2dfdd0865912bc34795acfe1584818614de8a4035b15e85718f1d132aaecffbb3e080acd50c52aa36ee3cdee0eff72edfd8e7";
        strMasternodePoolDummyAddress = "Yg7LVMahojABn7cxsEZdRHGdvLyVsCFxE3";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
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
        pchMessageStart[0] = 0x79; // y
        pchMessageStart[1] = 0x75; // u
        pchMessageStart[2] = 0x63; // c
        pchMessageStart[3] = 0x62; // b
        vAlertPubKey = ParseHex("04d661d3f8e8775f9ffa42b4df57f5b53217d229109b5606b619b678f6140668d07403385279dc8399d82cc2c2281b3d5904775086559c660708b9d9c67772a871");
        nDefaultPort = 22221;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // YUCOIN: 1 day
        nTargetSpacing = 2 * 60;  // YUCOIN: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1557916759;
        genesis.nNonce = 3339444;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000008ef772289b67f6801a278f7e0b98622b54aaf85ae9723fcc4748d62a834"));
        assert(genesis.hashMerkleRoot == uint256("0x9ef08e4a86a09c4a380ade8caa111d036b54edd43b28e56ff01aecc2b7512c71"));

        vFixedSeeds.clear();
        vSeeds.clear();

		vSeeds.push_back(CDNSSeedData("206.189.230.228", "206.189.230.228"));
        vSeeds.push_back(CDNSSeedData("139.59.177.177", "139.59.177.177"));
        vSeeds.push_back(CDNSSeedData("159.89.119.230", "159.89.119.230"));
        
        // Testnet YUCOIN addresses start with 'g'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 140);
        // Testnet YUCOIN script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 14);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 110);
        // Testnet YUCOIN BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x06)(0x42)(0x76)(0xCB).convert_to_container<std::vector<unsigned char> >();
        // Testnet YUCOIN BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x06)(0x39)(0x23)(0x64).convert_to_container<std::vector<unsigned char> >();
        // Testnet bitcoin green BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x70)(0x00)(0x00)(0x02).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04a1855446eb4dd3482c470681ceb2dfdd0865912bc34795acfe1584818614de8a4035b15e85718f1d132aaecffbb3e080acd50c52aa36ee3cdee0eff72edfd8e7";
        strMasternodePoolDummyAddress = "yhRgt7n2LbZjFRp21k8ufwCSd9CGrchWmM";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
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
        pchMessageStart[0] = 0x72; // r
        pchMessageStart[1] = 0x79; // y
        pchMessageStart[2] = 0x75; // u
        pchMessageStart[3] = 0x63; // c
        nDefaultPort = 22222;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // YUCOIN: 1 day
        nTargetSpacing = 1 * 60;        // YUCOIN: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1557913159;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();

       assert(hashGenesisBlock == uint256("0x2f8cb3e3acca6779d7fbe63a9d21d760a7a28f4fb793bdf12f2cefa4cda44867"));
       assert(genesis.hashMerkleRoot == uint256("0x9ef08e4a86a09c4a380ade8caa111d036b54edd43b28e56ff01aecc2b7512c71"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        // Testnet YUCOIN addresses start with 'g'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 122);
        // Testnet YUCOIN script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 14);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 106);
        // Testnet YUCOIN BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x37)(0x85)(0xD2).convert_to_container<std::vector<unsigned char> >();
        // Testnet YUCOIN BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x33)(0x85)(0x96).convert_to_container<std::vector<unsigned char> >();
        // Testnet bitcoin green BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x60)(0x00)(0x00)(0x02).convert_to_container<std::vector<unsigned char> >();

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
        nDefaultPort = 22223;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

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
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
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
        /*
        if(genesis.GetHash() != uint256("0x00000406ab84bf6cc23fd0c4d6fd64dcb43b2839ec880de3d2fccf4268687456"))
        {
              printf("MSearching for genesis block...\n");
              uint256 hashTarget;
              hashTarget.SetCompact(genesis.nBits);
              while(uint256(genesis.GetHash()) > uint256(hashTarget))
              {
                  ++genesis.nNonce;
                  if (genesis.nNonce == 0)
                  {
                      printf("Mainnet NONCE WRAPPED, incrementing time");
                      std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                      ++genesis.nTime;
                  }
                  if (genesis.nNonce % 10000 == 0)
                  {
                      printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                  }
              }
              printf("Mainnet block.nTime = %u \n", genesis.nTime);
              printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
              printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
              printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }        
        */