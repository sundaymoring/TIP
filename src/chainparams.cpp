// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"
#include "arith_uint256.h"

#include "versionbits.h"

using namespace std;

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{

	CMutableTransaction txNew;
	txNew.nTime = 1393221600;
	txNew.vin.resize(1);
	txNew.vout.resize(1);
	txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
	txNew.vout[0].SetEmpty();

	CBlock genesis;
	genesis.vtx.push_back(txNew);
	genesis.hashPrevBlock.SetNull();
	genesis.hashMerkleRoot = uint256S("12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90");
	genesis.nVersion = 1;
	genesis.nTime    = 1393221600;
	genesis.nBits    = 0x1e0fffff;
	genesis.nNonce   = 164482;
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
 *   Coinbase(hash=12630d16a9, ver=1, nTime=1393221600, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
 *     CTxOut(empty)
 *   vMerkleTree: 12630d16a9
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "20 Feb 2014 Bitcoin ATMs come to USA";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nMaxReorganizationDepth = 500;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("000000000000ffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nTargetTimespan = 60 * 60; // 16 mins
        consensus.nTargetSpacingV1 = 60;
        consensus.nTargetSpacing = 60;
        consensus.BIP34Height = 227931;
        consensus.BIP34Hash = uint256S("0x000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8");
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nTargetTimespan / nTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
//        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
//        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 999999999999ULL; // never
//        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 0; // out of time

        consensus.nProtocolV1RetargetingFixedTime = 1395631999;
        consensus.nProtocolV2Time = 1407053625;
        consensus.nProtocolV3Time = 1444028400;
        consensus.nLastPOWBlock = 1000;
        consensus.nStakeTimestampMask = 0xf;
        consensus.nForkBlockHeight = 87290;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
//        pchMessageStart[0] = 0x3E;
//        pchMessageStart[1] = 0xD6;
//        pchMessageStart[2] = 0x54;
//        pchMessageStart[3] = 0xD3;

        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0xD6;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0xD3;

        vAlertPubKey = ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284");
        nDefaultPort = 8111;
        nMaxTipAge = 24 * 60 * 60;
//        nMaxTipAge = 24 * 60 * 60 * 30;
        nPruneAfterHeight = 100000;

        /**
                 * Build the genesis block. Note that the output of its generation
                 * transaction cannot be spent since it did not originally exist in the
                 * database.
                 *
                 * CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
                 *   Coinbase(hash=12630d16a9, ver=1, nTime=1393221600, vin.size=1, vout.size=1, nLockTime=0)
                 *     CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
                 *     CTxOut(empty)
                 *   vMerkleTree: 12630d16a9
                 */
        const char* pszTimestamp = "It is inevitable that IP service and securitization powered by blockchain will stand in the center stage of the future startups since execution and management could be commoditized";
        CMutableTransaction txNew;
        txNew.nTime = 1520840985;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.nVersion = 1;
        genesis.nTime    = 1520840985;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce = 454493;
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        consensus.hashGenesisBlock = genesis.GetHash();
//        while (true) {
//            static int i= 0;
//            genesis.nNonce = ++i;
//            genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
//            consensus.hashGenesisBlock = genesis.GetHash();
//            if(i%10000==0){
//                printf( "i=%d consensus.hashGenesisBlock=%s\n", i, consensus.hashGenesisBlock.GetHex().c_str() );
//                printf( "arith_uint256().SetCompact(genesis.nBits)=%s\n", arith_uint256().SetCompact(genesis.nBits).GetHex().c_str());
//                printf( "aconsensus.powLimit=%s\n\n", consensus.powLimit.GetHex().c_str());
//            }
//            if(UintToArith256(consensus.hashGenesisBlock) < UintToArith256(consensus.powLimit) &&
//                    UintToArith256(consensus.hashGenesisBlock) < arith_uint256().SetCompact(genesis.nBits)){
//                printf( "i = %d\n", genesis.nNonce);
//                printf( "consensus.hashGenesisBlock=0x%s\n", consensus.hashGenesisBlock.GetHex().c_str());
//                printf( "genesis.hashMerkleRoot=0x%s\n", genesis.hashMerkleRoot.GetHex().c_str() );
//                break;
//            }
//        }
        assert(consensus.hashGenesisBlock == uint256S("0x000008e6a0786d4af0dd575edec94425f307a7d713bfc665f874e65e2eadfc1c"));
        assert(genesis.hashMerkleRoot == uint256S("0xb899ee5419372e0b91904866e63a3b16f3dac88557403701305ba26bdadf8e38"));

        vSeeds.push_back(CDNSSeedData("seed1.topipchain.bpchain.io", "seed1.topipchain.bpchain.io"));
        vSeeds.push_back(CDNSSeedData("seed2.topipchain.bpchain.io", "seed2.topipchain.bpchain.io"));
        vSeeds.push_back(CDNSSeedData("seed3.topipchain.bpchain.io", "seed3.topipchain.bpchain.io"));
        vSeeds.push_back(CDNSSeedData("seed4.topipchain.bpchain.io", "seed4.topipchain.bpchain.io"));
        vSeeds.push_back(CDNSSeedData("seed5.topipchain.bpchain.io", "seed5.topipchain.bpchain.io"));
        vSeeds.push_back(CDNSSeedData("seed6.topipchain.bpchain.io", "seed6.topipchain.bpchain.io"));
        vSeeds.push_back(CDNSSeedData("seed7.topipchain.bpchain.io", "seed7.topipchain.bpchain.io"));
        vSeeds.push_back(CDNSSeedData("seed8.topipchain.bpchain.io", "seed8.topipchain.bpchain.io"));
        vSeeds.push_back(CDNSSeedData("seed9.topipchain.bpchain.io", "seed9.topipchain.bpchain.io"));
        vSeeds.push_back(CDNSSeedData("seed10.topipchain.bpchain.io", "seed10.topipchain.bpchain.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,55);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,117);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1,153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData) {/*
                    boost::assign::map_list_of
                    (  5001, uint256S("0x2fac9021be0c311e7b6dc0933a72047c70f817e2eb1e01bede011193ad1b28bc"))  // hardfork
                    ( 10000, uint256S("0x0000000000827e4dc601f7310a91c45af8df0dfc1b6fa1dfa5b896cb00c8767c"))  // last pow block
                    ( 38425, uint256S("0x62bf2e9701226d2f88d9fa99d650bd81f3faf2e56f305b7d71ccd1e7aa9c3075"))  // hardfork
                    (254348, uint256S("0x9bf8d9bd757d3ef23d5906d70567e5f0da93f1e0376588c8d421a95e2421838b"))  // minor network split
                    (319002, uint256S("0x0011494d03b2cdf1ecfc8b0818f1e0ef7ee1d9e9b3d1279c10d35456bc3899ef"))  // hardfork
                    (872456, uint256S("0xe4fd321ced1de06213d2e246b150b4bfd8c4aa0989965dce88f2a58668c64860")), // hardfork
                    1444028528, // * UNIX timestamp of last checkpoint block
                    2774767,    // * total number of transactions between genesis and last checkpoint
                                //   (the tx=... number in the SetBestChain debug.log lines)
                    3500.0      // * estimated number of transactions per day after checkpoint
        */};
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 21111;
        consensus.BIP34Hash = uint256S("0x0000000023b3a96d3484e5abb3755c413e7d41500f8e2a5c3f0dd01299cd8ef8");
        consensus.powLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.nProtocolV1RetargetingFixedTime = 0;
        consensus.nProtocolV2Time = 0;
        consensus.nProtocolV3Time = 0;
        consensus.nLastPOWBlock = 0x7fffffff;
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 25714;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1411111111, 216178, 0x1f00ffff, 2, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();


        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("bitcoin.petertodd.org", "testnet-seed.bitcoin.petertodd.org"));
        vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));
        vSeeds.push_back(CDNSSeedData("bitcoin.schildbach.de", "testnet-seed.bitcoin.schildbach.de"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
			( 0, uint256S("0x0000724595fb3b9609d441cbfb9577615c292abf07d996d3edabc48de843642d")),
            0,
            0,
            0
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nMaxReorganizationDepth = 500;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nTargetTimespan = 16 * 60; // 16 mins
        consensus.nTargetSpacingV1 = 60;
        consensus.nTargetSpacing = 64;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nTargetTimespan / nTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
//        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
//        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 999999999999ULL; // never
//        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 0; // out of time

        consensus.nProtocolV1RetargetingFixedTime = 1400000000;
        consensus.nProtocolV2Time = 1410000000;
        consensus.nProtocolV3Time = 1420000000;
        consensus.nLastPOWBlock = 10000;
        consensus.nStakeTimestampMask = 0xf;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x70;
        pchMessageStart[1] = 0x35;
        pchMessageStart[2] = 0x22;
        pchMessageStart[3] = 0x06;
        vAlertPubKey = ParseHex("042508124261e3c969d9b4988349c41a329c6979e446facffc3227e16e5420c366e7d917e8ef80e70a27b90582272c93b6d0f16b0c728b970f73478167729cbbea");
        nDefaultPort = 25714;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 100000;

        /**
                 * Build the genesis block. Note that the output of its generation
                 * transaction cannot be spent since it did not originally exist in the
                 * database.
                 *
                 * CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
                 *   Coinbase(hash=12630d16a9, ver=1, nTime=1393221600, vin.size=1, vout.size=1, nLockTime=0)
                 *     CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
                 *     CTxOut(empty)
                 *   vMerkleTree: 12630d16a9
                 */
        const char* pszTimestamp = "20 Feb 2014 Bitcoin ATMs come to USA";
        CMutableTransaction txNew;
        txNew.nTime = 1393221600;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.nVersion = 1;
        genesis.nTime    = 1393221600;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce = 164482;
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        consensus.hashGenesisBlock = genesis.GetHash();
//        assert(consensus.hashGenesisBlock == uint256S("0x000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563"));
//        assert(genesis.hashMerkleRoot == uint256S("0x12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1,153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();


        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
			( 0, uint256S("0x000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563")),
            0,
            0,
            0
        };

    }
};
static CRegTestParams regTestParams;



static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

