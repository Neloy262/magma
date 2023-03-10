/*
 * Copyright (c) 2015, EURECOM (www.eurecom.fr)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of the FreeBSD Project.
 */

/*! \file 3gpp_23.401.h
  \brief
  \author Lionel Gauthier
  \company Eurecom
  \email: lionel.gauthier@eurecom.fr
*/
#ifndef FILE_3GPP_23_401_SEEN
#define FILE_3GPP_23_401_SEEN

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "lte/gateway/c/core/oai/lib/hashtable/hashtable.h"
#include "lte/gateway/c/core/oai/lib/hashtable/obj_hashtable.h"
#ifdef __cplusplus
}
#endif

#include "lte/gateway/c/core/oai/common/queue.h"

#include "lte/gateway/c/core/oai/lib/3gpp/3gpp_23.003.h"
#include "lte/gateway/c/core/oai/lib/3gpp/3gpp_24.007.h"
#include "lte/gateway/c/core/oai/lib/3gpp/3gpp_24.008.h"
#include "lte/gateway/c/core/oai/lib/3gpp/3gpp_29.274.h"
#include "lte/gateway/c/core/oai/common/common_types.h"
#include "lte/gateway/c/core/oai/include/s11_messages_types.hpp"
#include "lte/gateway/c/core/oai/include/gx_messages_types.h"

//==============================================================================
// 5.7 Information storage
//==============================================================================

//------------------------------------------------------------------------------
// 5.7.3 Serving GW
//------------------------------------------------------------------------------
// A primary key for a EPS Bearer entry  can be a tuple (eps bearer id, imsi)
typedef struct sgw_eps_bearer_ctxt_s {
  paa_t paa;
  ebi_t eps_bearer_id;  ///< An EPS bearer identity uniquely identifies an EPS
                        ///< bearer for one UE accessing via E-UTRAN
  traffic_flow_template_t tft;  ///< Traffic Flow Template

  ip_address_t
      p_gw_address_in_use_up;  ///< The IP address of the P-GW currently used
                               ///< for sending user plane traffic. (For
                               ///< GTP-based S5/S8 only).
  teid_t p_gw_teid_S5_S8_up;  ///< P-GW Tunnel Endpoint Identifier for the S5/S8
                              ///< interface for the user plane. (For GTP-based
                              ///< S5/S8 only).

  ip_address_t s_gw_ip_address_S5_S8_up;  ///< S-GW IP address for user plane
                                          ///< data received from PDN GW. (For
                                          ///< GTP-based S5/S8 only).
  teid_t s_gw_teid_S5_S8_up;  ///< S-GW Tunnel Endpoint Identifier for the S5/S8
                              ///< interface for the user plane. (For GTP-based
                              ///< S5/S8 only).

  ip_address_t
      s_gw_ip_address_S1u_S12_S4_up;  ///< S-GW IP address for the S1-u
                                      ///< interface (Used by the eNodeB), for
                                      ///< the S12 interface (used by the RNC)
                                      ///< and for the S4 interface (used by the
                                      ///< SGSN).
  teid_t s_gw_teid_S1u_S12_S4_up;  ///< S-GW Tunnel Endpoint Identifier for the
                                   ///< S1-u interface, for the S12 interface
                                   ///< (used by the RNC) and for the S4
                                   ///< interface (used by the SGSN).

  ip_address_t enb_ip_address_S1u;  ///< eNodeB IP address for the S1-u
                                    ///< interface (Used by the S-GW).
  teid_t enb_teid_S1u;  ///< eNodeB Tunnel Endpoint Identifier for the S1-u
                        ///< interface.

  // TODO CHECK
  bearer_qos_t eps_bearer_qos;  ///< ARP, GBR, MBR, QCI.
  // NOT NEEDED        charging_id                       ///< Charging
  // identifier, identifies charging records generated by S-GW and PDN GW.

  // SDF identifier
  uint8_t num_sdf;
  uint32_t sdf_id[TRAFFIC_FLOW_TEMPLATE_NB_PACKET_FILTERS_MAX];
  char policy_rule_name[POLICY_RULE_NAME_MAXLEN + 1];
  uint32_t sgw_sequence_number;
  char* pgw_cp_ip_port;
  bool update_teids;  // this is purely for optimization purposes and can be
                      // safely initialized to true
} sgw_eps_bearer_ctxt_t;

typedef struct sgw_pdn_connection_s {
  APN_t apn_in_use;  ///< The APN currently used, as received from the MME or S4
                     ///< SGSN.
  // NOT NEEDED NOW eps_pdn_charging                   ///< The charging
  // characteristics of this PDN connection, e.g.normal, prepaid, flat-rate
  // and/or hot billing. NOT IMPLEMENTED NOW
  ip_address_t
      p_gw_address_in_use_cp;  ///< The IP address of the P-GW currently used
                               ///< for sending control plane signalling.
  // NOT IMPLEMENTED NOW
  teid_t p_gw_teid_S5_S8_cp;  ///< P-GW Tunnel Endpoint Identifier for the S5/S8
                              ///< interface for the control plane. (For
                              ///< GTP-based S5/S8 only).
  // NOT IMPLEMENTED NOW
  ip_address_t
      p_gw_address_in_use_up;  ///< The IP address of the P-GW currently used
                               ///< for sending user plane traffic. (For
                               ///< PMIP-based S5/S8 only)
  // NOT NEEDED p_gw_gre_key_for_uplink_traffic_up     ///< PDN GW assigned GRE
  // Key for the S5/S8 interface for the user plane for uplink traffic. (For
  // PMIP-based S5/S8 only)
  ip_address_t s_gw_ip_address_S5_S8_cp;  ///< S-GW IP address for the S5/S8 for
                                          ///< the control plane signalling.
  teid_t s_gw_teid_S5_S8_cp;  ///< S-GW Tunnel Endpoint Identifier for the S5/S8
                              ///< control plane interface. (For GTP-based S5/S8
                              ///< only).
  ip_address_t
      s_gw_address_in_use_up;  ///< The IP address of the S-GW currently used
                               ///< for sending user plane traffic. (For
                               ///< PMIP-based S5/S8 only)
  // NOT NEEDED s_gw_gre_key_for_dl_traffic_up         ///< user plane for
  // downlink traffic. (For PMIP-based S5/S8 only)
  ebi_t default_bearer;  ///< Identifies the default bearer within the PDN
                         ///< connection by its EPS Bearer Id. (For PMIP based
                         ///< S5/S8.)
  bool ue_suspended_for_ps_handover;  ///< Suspend Notification is received from
                                      ///< MME, which would
  ///< indicate that CSFB is invoked and UE doesn't have the support
  ///< for PS handover, so move the UE to suspended state and
  ///< SPGW shall discard the DL data.

  // eps bearers
  sgw_eps_bearer_ctxt_t* sgw_eps_bearers_array[BEARERS_PER_UE];

} sgw_pdn_connection_t;

/** @struct sgw_eps_bearer_context_information_t
 *  @brief Useful parameters to know in SGW application layer. They are set
 * according to 3GPP TS.23.401 #5.7.3
 */
// The Serving GW maintains the following EPS bearer context information for
// UEs. Struct sgw_eps_bearer_context_information_t contain the context fields
// for one UE.
typedef struct sgw_eps_bearer_context_information_s {
  Imsi_t imsi;      ///< IMSI (International Mobile Subscriber Identity) is the
                    ///< subscriber permanent identity.
  imsi64_t imsi64;  ///< IMSI in 64 bit integer format
  int8_t imsi_unauthenticated_indicator;  /// This is an IMSI indicator to show
                                          /// the IMSI is unauthenticated.
  // TO BE CHECKED me_identity_t    me_identity;       ///< Mobile Equipment
  // Identity (e.g. IMEI/IMEISV).
  char msisdn[MSISDN_LENGTH];  ///< The basic MSISDN of the UE. The presence is
                               ///< dictated by its storage in the HSS.
  // NOT NEEDED selected_cn_operator_id                ///< Selected core
  // network operator identity (to support networksharing as defined in
  // TS 23.251
  teid_t
      mme_teid_S11;  ///< MME Tunnel Endpoint Identifier for the S11 interface
  ip_address_t mme_ip_address_S11;  ///< MME IP address the S11 interface.
  teid_t s_gw_teid_S11_S4;  ///< S-GW Tunnel Endpoint Identifier for the S11
                            ///< Interface and the S4 Interface (control plane)
  ip_address_t
      s_gw_ip_address_S11_S4;  ///< S-GW IP address for the S11 interface and
                               ///< the S4 Interface (control plane).
  // NOT NEEDED Trace reference                        ///< Identifies a record
  // or a collection of records for a particular trace. NOT NEEDED Trace type
  // ///< Indicates the type of trace NOT NEEDED Trigger id ///< Identifies the
  // entity that initiated the trace NOT NEEDED OMC identity ///< Identifies the
  // OMC that shall receive the trace record(s).
  ecgi_t last_known_cell_Id;  ///< This is the last location of the UE known by
                              ///< the network
  // NOT NEEDED NOW Last known Cell Id age             ///< This is the age of
  // the above UE location information

  // TODO more than one PDN connection;
  sgw_pdn_connection_t pdn_connection;

  void* trxn;
  // TODO change this saved_message (add procedure/transaction)
  itti_s11_create_session_request_t saved_message;
  LIST_HEAD(pending_procedures_s, pgw_base_proc_s) * pending_procedures;

} sgw_eps_bearer_context_information_t;

//------------------------------------------------------------------------------
// 5.7.4 PDN GW
//------------------------------------------------------------------------------

// The PDN GW maintains the following EPS bearer context information for UEs.
// For emergency attached UEs which are not authenticated, IMEI is stored in
// context.
typedef struct pgw_eps_bearer_context_information_s {
  Imsi_t imsi;  ///< IMSI (International Mobile Subscriber Identity) is the
                ///< subscriber permanent identity.
  int8_t imsi_unauthenticated_indicator;  ///< This is an IMSI indicator to show
                                          ///< the IMSI is unauthenticated.
  // TO BE CHECKED me_identity_t    me_identity;       ///< Mobile Equipment
  // Identity (e.g. IMEI/IMEISV).
  char msisdn[MSISDN_LENGTH];  ///< The basic MSISDN of the UE. The presence is
                               ///< dictated by its storage in the HSS.
  // NOT NEEDED selected_cn_operator_id                ///< Selected core
  // network operator identity (to support networksharing as defined in
  // TS 23.251
  rat_type_t rat_type;  ///< Current RAT
  // NOT NEEDED Trace reference                        ///< Identifies a record
  // or a collection of records for a particular trace. NOT NEEDED Trace type
  // ///< Indicates the type of trace NOT NEEDED Trigger id ///< Identifies the
  // entity that initiated the trace NOT NEEDED OMC identity ///< Identifies the
  // OMC that shall receive the trace record(s).

  // TO BE CONTINUED...
  obj_hash_table_t* apns;
} pgw_eps_bearer_context_information_t;

// For each APN in use:
typedef struct pgw_apn_s {
  APN_t apn_in_use;  ///< The APN currently used, as received from the S-GW.
  ambr_t apn_ambr;   ///<  The maximum aggregated uplink and downlink MBR values
                     ///<  to be shared across all Non-GBR bearers,
  ///   which are established for this APN.
  obj_hash_table_t*
      pdn_connections;  ///<  For each PDN Connection within the APN
} pgw_apn_t;

typedef struct pgw_pdn_connection_s {
  // ip_addresses;                                       ///< IPv4 address
  // and/or IPv6 prefix
  pdn_type_t pdn_type;  ///< IPv4, IPv6, or IPv4v6
  ip_address_t
      s_gw_address_in_use_cp;  ///< The IP address of the S-GW currently used
                               ///< for sending control plane signalling.
  teid_t s_gw_teid_S5_S8_cp;  ///< S-GW Tunnel Endpoint Identifier for the S5/S8
                              ///< interface for the control plane. (For
                              ///< GTP-based S5/S8 only).
  ip_address_t
      s_gw_address_in_use_up;  ///< The IP address of the S-GW currently used
                               ///< for sending user plane traffic. (For
                               ///< PMIP-based S5/S8 only).
  // NOT NEEDED s_gw_gre_key_for_dl_traffic_up         ///< Serving GW assigned
  // GRE Key for the S5/S8 interface for the user plane for downlink traffic.
  // (For PMIP-based S5/S8 only).
  ip_address_t p_gw_ip_address_S5_S8_cp;  ///< P-GW IP address for the S5/S8 for
                                          ///< the control plane signalling.
  teid_t p_gw_teid_S5_S8_cp;  ///< P-GW Tunnel Endpoint Identifier for the S5/S8
                              ///< control plane interface. (For GTP-based S5/S8
                              ///< only).
  ip_address_t
      p_gw_address_in_use_up;  ///< The IP address of the P-GW currently used
                               ///< for sending user plane traffic. (For
                               ///< PMIP-based S5/S8 only).
  // NOT NEEDED p_gw_gre_key_for_uplink_traffic_up     ///< PDN GW assigned GRE
  // Key for the S5/S8 interface for the user plane for uplink traffic. (For
  // PMIP-based S5/S8 only). NOT NEEDED MS Info Change Reporting Action ///<
  // Denotes whether the MME and/or the SGSN is/are requested to send changes in
  // User Location Information change for this bearer. NOT NEEDED CSG
  // Information Reporting Action       ///< Denotes whether the MME and/or the
  // SGSN is/are requested to send changes in User CSG Information change for
  // this bearer.
  ///  This field denotes separately whether the MME/SGSN are requested to send
  ///  changes in User CSG Information for (a) CSG cells, (b) hybrid cells in
  ///  which the subscriber is a CSG member, and (c) hybrid cells in which the
  ///  subscriber is not a CSG member, or any combination of the above.
  ebi_t default_bearer;  ///< Identifies the default bearer within the PDN
                         ///< connection by its EPS Bearer Id. The default
                         ///< bearer is the one which is established first
                         ///< within the PDN connection. (For GTP based
  ///  S5/S8 or for PMIP based S5/S8 if multiple PDN connections to the same APN
  ///  are supported).

  hash_table_t* pgw_eps_bearers;
} pgw_pdn_connection_t;

typedef struct pgw_eps_bearer_entry_gtp_based_S5_S8_only_s {
  ebi_t eps_bearer_id;  ///< An EPS bearer identity uniquely identifies an EPS
                        ///< bearer for one UE accessing via E-UTRAN
  // TO DO traffic_flow_template_t tft;                   ///< Traffic Flow
  // Template

  ip_address_t
      s_gw_address_in_use_up;  ///< The IP address of the S-GW currently used
                               ///< for sending user plane traffic.
  teid_t s_gw_teid_S5_S8_up;  ///< S-GW Tunnel Endpoint Identifier for the S5/S8
                              ///< interface for the user plane.

  ip_address_t p_gw_ip_address_S5_S8_up;  ///< P-GW IP address for user plane
                                          ///< data received from PDN GW.
  teid_t p_gw_teid_S5_S8_up;  ///< P-GW Tunnel Endpoint Identifier for the GTP
                              ///< Based S5/S8 interface for user plane.

  // TO BE CHECKED
  bearer_qos_t eps_bearer_qos;  ///< ARP, GBR, MBR, QCI.
  // NOT NEEDED        charging_id                        ///< Charging
  // identifier, identifies charging records generated by S-GW and PDN GW.

} pgw_eps_bearer_entry_t;

#endif /* FILE_3GPP_23_401_SEEN */
