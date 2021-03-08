#ifndef THTTPDEFINE_H
#define THTTPDEFINE_H

#define HTTP_REQUEST_TIMEOUT 5000

#define _REQUEST_HTTP_MSG         100000

#define _REQUEST_HTTP_SENDGET                _REQUEST_HTTP_MSG   + 101
#define _REQUEST_HTTP_SENDPOST               _REQUEST_HTTP_MSG   + 102
#define _REQUEST_HTTP_SENDFILE               _REQUEST_HTTP_MSG   + 103
#define _REQUEST_HTTP_DOWNFILE               _REQUEST_HTTP_MSG   + 104
#define _REQUEST_HTTP_UPLOADDUMP             _REQUEST_HTTP_MSG   + 105

// 用来区分请求设备
#define DEVICE_TYPE "winclient"

#endif // THTTPDEFINE_H
