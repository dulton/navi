/*
* The UrbanEye PND solution is a collection of packages based on native C++ classes
* that implement the fundamental algorithms & operations required to satisfy one kind
* of mobile or portable devices with competitive qualities being a leading one.
*
* Copyright (C) 2008 Xiujie Sheng
*
* This library isn't a free software, so you cann't take the sourcecode without author's permit.
* Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
* if you illegally got it. 
*
* NOTE: 
* AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
* LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
*
* For more information, contact:
*
* China University of Geoseciences(Wuhan)
* Graduate School
*
* Xiujie Sheng
* smartpoint@sohu.com
*/
#ifndef _UEMODEL_ROADNETWORK_H
#define _UEMODEL_ROADNETWORK_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Import the common definitions of one network
#ifndef _UEMODEL_UEBASIC_H
#include "netbasic.h"
#endif

//
#ifndef _UEMODEL_NETPARCEL_H
#include "netparcel.h"
#endif

// Refer to self-array definition
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif

// Refer to 
#ifndef _UEBASE_SIMPLELRU_H
#include "uebase\simplelru.h"
#endif

// Refer to memory garbage
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif

// Refer to mediator
#ifndef _UEBASE_MEDIATOR_H
#include "uebase\mediator.h"
#endif
using namespace UeBase;

// Refer to index mechansim
#ifndef _UEINDEX_INDEXIMPL_H
#include "ueindex\geoindeximpl.h"
#endif
using namespace UeIndex;

// Compiler setting
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z

// Declare namespace
namespace UeModel
{
  // Forward classes
  class INetGateWay;
  class INetLink;
  class INetNode;
  class INetAllocator;
  class INameTable;

  /**
  * \brief ·�����ʽӿ�
  * Characters:
  * 1) Simply use Link and Node to represent one road network
  * 2) This road network is multiple, namely, it includes different data gates representing one road network
  * 3) The index way of mutiple networks would be organized as "layer-tile" structure
  */
  class UEMODEL_CLASS IRoadNetwork
  {
  public:
    /// Name aliases for different data sources
    typedef std::map<short, INetGateWay*> GateMap;
    typedef GateMap::iterator gate_itr;
    typedef GateMap::const_iterator gate_citr;

    /// Name Aliases for different character sets
    typedef std::map<short, INameTable*> NameTableMap;
    typedef NameTableMap::iterator name_itr;
    typedef NameTableMap::const_iterator name_citr;

    /// Cache
    typedef CSimpleLru<INetParcel> NetCacheWay;

    /**
    * \brief Different modes when loading one parcel
    */
    enum LoadMode
    {
      LM_All = 0,
      LM_NoRTree,
      LM_Lazy         // Only load basic parcel definition not content
    };

  private:
    //
    // Constructors and deconstrcutor
    //
    /**
    * \brief Being factory method to build one kind of network
    */
    IRoadNetwork(GateMap &directGates, GateMap &mappingGates, NameTableMap &nameTables, CGeoIndexImpl *indexWay, NetCacheWay *cacheWay, INetAllocator *allocator);

    /**
    * \brief ��������
    */
    ~IRoadNetwork();

  public:
    //
    // Methods as a singleton
    //
    /**
    * \brief Release this road network
    */
    void Delete();

    /**
    * \brief Use singletion to replace the reference number of this object
    *
    * TODO:
    * To make sure whether it is reasonable that constructing index mechansim for this road network
    */
    static IRoadNetwork *GetNetwork(GateMap &directGates, GateMap &mappingGates, NameTableMap &nameTables, CGeoIndexImpl *indexWay, NetCacheWay *cacheWay, INetAllocator *allocator);

    /**
    * \brief ����UeModel,���IRoadNetwork�ӿ�
    */
    static IRoadNetwork *GetNetwork();

    //
    // Multiple layers based on tile-layer structure
    //
    /**
    * \brief Generally there are only one tile in one layer
    */
    short GatewayID(short layerID, short tileID = 0);

    /**
    * \brief Spatially define which data source
    */
    short GatewayID(short layerID, CGeoPoint<double> &location);

    /**
    * \brief Get specified data gate directly using one type
    */
    INetGateWay* GateWay(short gateID);

    /**
    * \brief ��ȡָ��layer��ID
    **/
    short GetLayerID(short gateID);

    /**
    * \brief ��ȡָ��tile��ID
    **/
    short GetTileID(short gateID);

    /**
    * \brief ��ȡ�ܵ�gate��
    **/
    short GateCount()
    {
      return static_cast<short>(m_gateWays.size());
    }

    /**
    * \brief Add one data gate 
    */
    bool AddGateWay(short gateID, const tstring &gateName);

    /**
    * \brief Delete one data gate 
    */
    bool RemoveGateWay(short gateID);

    //
    // Access to other main components of one road network
    //
    /**
    * \brief ��ȡָ�������Ʊ���ʶ���
    * Default is NL_English
    */
    INameTable *GetNameTable(short type = UeModel::UNT_Network);

    /**
    * \brief ��ȡ�ڴ������
    * Note: the unique value allocation solution defautly is adopt long type
    */
    INetAllocator *GetAllocator();


    /**
    * \brief �л�gate
    **/
    void SwitchGates(bool isDirect = true);

    //
    //
    //
    /**
    * \brief ��ȡ�ܵ�������
    */
    long GetParcelCount(short gateID);

    /**
    * \brief ��ȡָ��gate�����½ǵ���������
    */
    INetParcel *FirstParcel(short gateID, short mode = LM_Lazy);

    /**
    * \brief ���������У���ȡ��һ���������
    */
    INetParcel *NextParcel(short gateID, long &prevID, short mode = LM_Lazy);

    /**
    * \brief Get one parcel specified to one of multiple networks
    */
    INetParcel *GetParcel(short gateID, long parcelID, short mode = LM_All);

    /**
    * \brief ��ȡָ��gate��ָ��λ���������������
    */
    INetParcel *GetParcel(short gateID, CGeoPoint<long> &pos, short mode = LM_All);

    /**
    * \brief ��ȡָ��gate��ָ��λ�����������������
    */
    long GetParcelID(short gateID, CGeoPoint<long> &pos);

    /**
    * \brief ��ȡָ��gate��ָ�����������漰���������������
    */
    bool GetParcelID(short gateID, CGeoRect<long> &mbr, double tolerance, CMemVector& indice);

    /**
    * \brief Assume the coordinates in network is represented by long type
    */
    void GetParcelMBR(short gateID, long parcelID, CGeoRect<double> &mbr);

    /**
    * \brief ��ȡָ��gate��ָ��λ����������ı߽����
    */
    void GetParcelMBR(short gateID, CGeoPoint<double> &point, CGeoRect<double> &mbr);

    /**
    * \brief Remove the LRU
    */
    void ReleaseParcel();

    /**
    * \brief �ӻ��������ָ��gate����������
    */
    void ReleaseParcel(short gateID);

    /**
    * \brief �ӻ��������ָ��gate��ָ�����������
    */
    void ReleaseParcel(short gateID, long parcelID);

    /**
    * \brief Really update one data source with taking one parcel as unit
    */
    bool UpdateParcel(short gateID, INetParcel *oneParcel);


    //
    // Spatially or directly get network primitives against efficient cache mechansim way
    //
    /**
    * \brief ��ָ��gate�л�ȡָ�����η�Χ�ڵ�����·��
    */
    void GetLinks(short gateID, CGeoRect<double> &mbr, double tolerance, CMemVector& links);

    /**
    * \brief ��ָ��gate�л�ȡָ�����η�Χ�ڵ����н��
    */
    void GetNodes(short gateID, CGeoRect<double> &mbr, double tolerance, CMemVector &nodes);

    /**
    * \brief ��ָ��gate�л�ȡָ���������ض��������ӽ��
    */
    INetNode *GetAdjacentNode(short gateID, long &parcelID, long &nodeID, INetParcel *curParcel, INetNode *oneNode);

    /**
    * \brief ��ָ��gate�л�ȡָ���������ض������ϲ���
    */
    INetNode *GetUpNode(short gateID, long &parcelID, long &nodeID, INetParcel *curParcel, INetNode *oneNode);

    /**
    * \brief ��ָ��gate�л�ȡָ���������ض������²���
    */
    INetNode *GetDownNode(short gateID, long &parcelID, long &nodeID, INetParcel *curParcel, INetNode *oneNode);

    //
    //
    //
    /**
    * \brief ���û���Ĵ�С
    */
    void SetCacheSize(int size);

    /**
    * \brief ȡ�����л���Ĵ�С
    */
    int GetCacheSize();

    /**
    * \brief ����ָ��gate��LRU����
    */
    void EraseLRU(int gateID);

    /**
    *
    */
    void MakeXOR(std::vector<int> &ids);

    //
    //
    //
    /**
    * \brief ע����Դ������ 
    */
    void RegisterGarbage(CMemoryGarbage *garbage);

    /**
    * \brief ��ȡ��Դ������
    */
    CMemoryGarbage *GetGarbage();

    /**
    * \brief ע���н���
    */
    void RegisterMediator(CMediator *mediator);

    /**
    * \brief ȡ���н���
    */
    CMediator *GetMediator();

    /**
    * \brief ������Դ
    */
    bool ForCollegues();

  private:
    // Multiple data gate ways
    // Note: Below structure should also support repeated gate ways beloinging to different data sources
    // Namely, key value should corresponds to the unique data directory or data source
    GateMap m_directGates;
    GateMap m_mappingGates;
    GateMap m_gateWays;
    bool m_isUseDirect;

    /// Index mechansim for this road network definition
    CGeoIndexImpl *m_indexWay;

    /// The conversion of one cache mechansim
    NetCacheWay *m_cacheWay;

    /// Name table 
    NameTableMap m_nameTables;

    /// Net allocator for assigning unqiue value
    INetAllocator *m_allocator;

    /// Memory collector
    CMemoryGarbage *m_garbage;

    /// Mediator
    CMediator *m_mediator;

    /// Singleton
    static IRoadNetwork *m_network;
  };
}

#endif
