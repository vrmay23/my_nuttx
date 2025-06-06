# ##############################################################################
# libs/libc/net/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

set(SRCS
    lib_addrconfig.c
    lib_base64.c
    lib_htons.c
    lib_htonl.c
    lib_htonq.c
    lib_inetaddr.c
    lib_inetaton.c
    lib_inetntoa.c
    lib_inetntop.c
    lib_inetpton.c
    lib_inetnetwork.c
    lib_etherntoa.c
    lib_etheraton.c)

if(CONFIG_NET)
  list(APPEND SRCS lib_accept.c)
endif()

if(CONFIG_NET_LOOPBACK)
  list(APPEND SRCS lib_loopback.c)
endif()

if(CONFIG_NETDEV_IFINDEX)
  list(
    APPEND
    SRCS
    lib_getifaddrs.c
    lib_freeifaddrs.c
    lib_indextoname.c
    lib_nametoindex.c
    lib_nameindex.c
    lib_freenameindex.c)
endif()

# Routing table support

if(CONFIG_NET_ROUTE)
  list(APPEND SRCS lib_addroute.c lib_delroute.c)
endif()

target_sources(c PRIVATE ${SRCS})
