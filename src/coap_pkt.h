#ifndef __COAP_PKT_H__
#define __COAP_PKT_H__

#include "coap_type.h"
#include "queue.h"

#define COAP_PKT_MAX_SIZE                      1280

#define COAP_PKT_MAKE_CODE(M, N)               ((M<<5) | N)

#define COAP_PKT_TYPE_CON                      0
#define COAP_PKT_TYPE_NON                      1
#define COAP_PKT_TYPE_ACK                      2
#define COAP_PKT_TYPE_RST                      3

#define COAP_PKT_CODE_GET                      COAP_PKT_MAKE_CODE(0, 1)
#define COAP_PKT_CODE_POST                     COAP_PKT_MAKE_CODE(0, 2)
#define COAP_PKT_CODE_PUT                      COAP_PKT_MAKE_CODE(0, 3)
#define COAP_PKT_CODE_DELETE                   COAP_PKT_MAKE_CODE(0, 4)
#define COAP_PKT_CODE_OK                       COAP_PKT_MAKE_CODE(2, 0)
#define COAP_PKT_CODE_CREATED                  COAP_PKT_MAKE_CODE(2, 1)
#define COAP_PKT_CODE_DELETED                  COAP_PKT_MAKE_CODE(2, 2)
#define COAP_PKT_CODE_VALID                    COAP_PKT_MAKE_CODE(2, 3)
#define COAP_PKT_CODE_CHANGED                  COAP_PKT_MAKE_CODE(2, 4)
#define COAP_PKT_CODE_CONTENT                  COAP_PKT_MAKE_CODE(2, 5)
#define COAP_PKT_CODE_BAD_REQUEST              COAP_PKT_MAKE_CODE(4, 0)
#define COAP_PKT_CODE_UNAUTHORIZED             COAP_PKT_MAKE_CODE(4, 1)
#define COAP_PKT_CODE_BAD_OPTION               COAP_PKT_MAKE_CODE(4, 2)
#define COAP_PKT_CODE_FORBIDDEN                COAP_PKT_MAKE_CODE(4, 3)
#define COAP_PKT_CODE_NOT_FOUND                COAP_PKT_MAKE_CODE(4, 4)
#define COAP_PKT_CODE_METHOD_NOT_ALLOWED       COAP_PKT_MAKE_CODE(4, 5)
#define COAP_PKT_CODE_NOT_ACCEPTABLE           COAP_PKT_MAKE_CODE(4, 6)
#define COAP_PKT_CODE_PRECONDITION_FAILED      COAP_PKT_MAKE_CODE(4, 12)
#define COAP_PKT_CODE_REQUEST_ENTITY_TOO_LARGE COAP_PKT_MAKE_CODE(4, 13)
#define COAP_PKT_CODE_UNSUPPORTED_MEDIA_TYPE   COAP_PKT_MAKE_CODE(4, 15)
#define COAP_PKT_CODE_INTERNAL_SERVER_ERROR    COAP_PKT_MAKE_CODE(5, 0)
#define COAP_PKT_CODE_NOT_IMPLEMENTED          COAP_PKT_MAKE_CODE(5, 1)
#define COAP_PKT_CODE_BAD_GATEWAY              COAP_PKT_MAKE_CODE(5, 2)
#define COAP_PKT_CODE_SERVICE_UNAVAILABLE      COAP_PKT_MAKE_CODE(5, 3)
#define COAP_PKT_CODE_GATEWAY_TIMEOUT          COAP_PKT_MAKE_CODE(5, 4)
#define COAP_PKT_CODE_PROXYING_NOT_SUPPORTED   COAP_PKT_MAKE_CODE(5, 5)

#define COAP_PKT_OPTION_IF_MATCH               1
#define COAP_PKT_OPTION_URI_HOST               3
#define COAP_PKT_OPTION_ETAG                   4
#define COAP_PKT_OPTION_IF_NONE_MATCH          5
#define COAP_PKT_OPTION_URI_PORT               7
#define COAP_PKT_OPTION_LOCATION_PATH          8
#define COAP_PKT_OPTION_URI_PATH               11
#define COAP_PKT_OPTION_CONTENT_FORMAT         12
#define COAP_PKT_OPTION_MAXAGE                 14
#define COAP_PKT_OPTION_URI_QUERY              15
#define COAP_PKT_OPTION_ACCEPT                 17
#define COAP_PKT_OPTION_LOCATION_QUERY         20
#define COAP_PKT_OPTION_PROXY_URI              35
#define COAP_PKT_OPTION_PROXY_SCHEME           39
#define COAP_PKT_OPTION_SIZE1                  60

#define COAP_PKT_IS_EMPTY(MSG)                 ((MSG)->code == 0)
#define COAP_PKT_IS_REQUEST(MSG)               (!COAP_PKT_IS_EMPTY(MSG) && ((MSG)->code < 32))
#define COAP_PKT_IS_RESPONSE(MSG)              ((MSG)->code >= 64)

#pragma pack(1)

typedef struct {
	uint8  token_length:4;
	uint8  type:2;
	uint8  version:2;
	uint8  code;
	uint16 message_id;
	uint8  token[1];
} coap_hdr_t;

#pragma pack()

typedef struct {
	queue_hdr_t node;
	size_t      size;
	uint8 *     p_option;
	uint8 *     p_data;
	size_t      packet_length;
	size_t      option_length;
	size_t      data_length;
	uint16      max_delta;
	uint32      last_transmit_time;
	uint32      retransmit_count;
	uint32      retransmit_interval;
	coap_hdr_t  hdr;
} coap_pkt_t;

coap_pkt_t * coap_pkt_alloc(size_t len);
coap_pkt_t * coap_pkt_parse(uint8 * p_data, size_t len);
int coap_pkt_free(coap_pkt_t * p_pkt);
int coap_pkt_add_header(coap_pkt_t * p_pkt, uint8 type, uint8 code, uint16 message_id);
int coap_pkt_add_token(coap_pkt_t * p_pkt, uint8 * token_data, size_t token_len);
int coap_pkt_add_option(coap_pkt_t * p_pkt, uint16 option_type, char * option_data, size_t option_len);
int coap_pkt_add_data(coap_pkt_t * p_pkt, uint8 * data, size_t data_len);

#endif
