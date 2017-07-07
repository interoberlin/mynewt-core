/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <inttypes.h>
#include <errno.h>

#include "host/ble_gap.h"
#include "host/ble_l2cap.h"
#include "console/console.h"
#include "btshell.h"
#include "cmd.h"
#include "cmd_l2cap.h"


/*****************************************************************************
 * $l2cap-update                                                             *
 *****************************************************************************/

int
cmd_l2cap_update(int argc, char **argv)
{
    struct ble_l2cap_sig_update_params params;
    uint16_t conn_handle;
    int rc;

    rc = parse_arg_all(argc - 1, argv + 1);
    if (rc != 0) {
        return rc;
    }

    conn_handle = parse_arg_uint16("conn", &rc);
    if (rc != 0) {
        console_printf("invalid 'conn' parameter\n");
        return rc;
    }

    params.itvl_min = parse_arg_uint16_dflt("interval_min",
                                            BLE_GAP_INITIAL_CONN_ITVL_MIN,
                                            &rc);
    if (rc != 0) {
        console_printf("invalid 'interval_min' parameter\n");
        return rc;
    }

    params.itvl_max = parse_arg_uint16_dflt("interval_max",
                                            BLE_GAP_INITIAL_CONN_ITVL_MAX,
                                            &rc);
    if (rc != 0) {
        console_printf("invalid 'interval_max' parameter\n");
        return rc;
    }

    params.slave_latency = parse_arg_uint16_dflt("latency", 0, &rc);
    if (rc != 0) {
        console_printf("invalid 'latency' parameter\n");
        return rc;
    }

    params.timeout_multiplier = parse_arg_uint16_dflt("timeout", 0x0100, &rc);
    if (rc != 0) {
        console_printf("invalid 'timeout' parameter\n");
        return rc;
    }

    rc = btshell_l2cap_update(conn_handle, &params);
    if (rc != 0) {
        console_printf("error txing l2cap update; rc=%d\n", rc);
        return rc;
    }

    return 0;
}

/*****************************************************************************
 * $l2cap-create-server                                                      *
 *****************************************************************************/

int
cmd_l2cap_create_server(int argc, char **argv)
{
    uint16_t psm = 0;
    int rc;

    rc = parse_arg_all(argc - 1, argv + 1);
    if (rc != 0) {
        return rc;
    }

    psm = parse_arg_uint16("psm", &rc);
    if (rc != 0) {
        console_printf("invalid 'psm' parameter\n");
        return rc;
    }

    rc = btshell_l2cap_create_srv(psm);
    if (rc) {
        console_printf("Server create error: 0x%02x", rc);
    }

    return 0;
}

/*****************************************************************************
 * $l2cap-connect                                                            *
 *****************************************************************************/

int
cmd_l2cap_connect(int argc, char **argv)
{
    uint16_t conn = 0;
    uint16_t psm = 0;
    int rc;

    rc = parse_arg_all(argc - 1, argv + 1);
    if (rc != 0) {
        return rc;
    }

    conn = parse_arg_uint16("conn", &rc);
    if (rc != 0) {
        console_printf("invalid 'conn' parameter\n");
    }

    psm = parse_arg_uint16("psm", &rc);
    if (rc != 0) {
        console_printf("invalid 'psm' parameter\n");
        return rc;
    }

    return btshell_l2cap_connect(conn, psm);
}

/*****************************************************************************
 * $l2cap-disconnect                                                         *
 *****************************************************************************/

int
cmd_l2cap_disconnect(int argc, char **argv)
{
    uint16_t conn;
    uint16_t idx;
    int rc;

    rc = parse_arg_all(argc - 1, argv + 1);
    if (rc != 0) {
        return rc;
    }

    conn = parse_arg_uint16("conn", &rc);
    if (rc != 0) {
        console_printf("invalid 'conn' parameter\n");
    }

    idx = parse_arg_uint16("idx", &rc);
    if (rc != 0) {
        console_printf("invalid 'idx' parameter\n");
        return 0;
    }

    return btshell_l2cap_disconnect(conn, idx);
}