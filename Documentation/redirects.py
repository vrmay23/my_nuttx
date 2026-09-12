# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.

"""Redirect map for pages that were moved or merged.

Every documentation page that is renamed, moved or merged into another one
MUST get an entry here.  The NuttX documentation is linked to from issues,
mailing list archives, blog posts and slide decks going back many years;
without these redirects a reorganisation silently breaks all of them.

The mapping is consumed by the ``sphinx_reredirects`` extension and is
keyed by the *old* document name (no extension, path relative to the
documentation root).  The value is the *new* location, relative to the old
page's directory -- see the sphinx-reredirects documentation.

Keep the entries grouped by the change that introduced them and keep each
group sorted, so that the file stays reviewable as it grows.
"""

redirects = {}
