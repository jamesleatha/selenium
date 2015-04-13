// Licensed to the Software Freedom Conservancy (SFC) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership. The SFC licenses this file
// to you under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

wchar_t* DELETECOOKIES[] = {
L"(function() { return function(){ \n",
L"var trim = function(str) { return str.replace(/^\\s*/, '').replace(/\\s*$/, ''); }\n",
L"var getCookieByName = function(cookieName, doc) {\n",
L"    var ck = document.cookie;\n",
L"    if (!ck) return null;\n",
L"    var ckPairs = ck.split(/;/);\n",
L"    for (var i = 0; i < ckPairs.length; i++) {\n",
L"        var ckPair = trim(ckPairs[i]);\n",
L"        var ckNameValue = ckPair.split(/=/);\n",
L"        var ckName = decodeURIComponent(ckNameValue[0]);\n",
L"        if (ckName === cookieName) {\n", 
L"            return decodeURIComponent(ckNameValue[1]);\n",
L"        }\n",
L"    }\n",
L"    return null;\n",
L"};\n",
L"var deleteCookie = function(cookieName, domain, path, doc) {\n",
L"    var expireDateInMilliseconds = new Date(1).toGMTString();\n",
L"    var cookie = cookieName + '=deleted; ';\n",
L"    if (path) {\n",
L"        cookie += 'path=' + path + '; ';\n",
L"    }\n",
L"    if (domain) {\n",
L"        cookie += 'domain=' + domain + '; ';\n",
L"    }\n",
L"    cookie += 'expires=' + expireDateInMilliseconds;\n",
L"    document.cookie = cookie;\n",
L"};\n",
L"var _maybeDeleteCookie = function(cookieName, domain, path, doc) {\n",
L"    deleteCookie(cookieName, domain, path, doc);\n",
L"    return false;\n",
L"};\n",
L"var _recursivelyDeleteCookieDomains = function(cookieName, domain, path, doc) {\n",
L"    var deleted = _maybeDeleteCookie(cookieName, domain, path, doc);\n",
L"    if (deleted) return true;\n",
L"    var dotIndex = domain.indexOf('.');\n",
L"    if (dotIndex == 0) {\n",
L"        return _recursivelyDeleteCookieDomains(cookieName, domain.substring(1), path, doc);\n",
L"    } else if (dotIndex != -1) {\n",
L"        return _recursivelyDeleteCookieDomains(cookieName, domain.substring(dotIndex), path, doc);\n",
L"    } else {\n",
L"        // No more dots; try just not passing in a domain at all\n",
L"        return _maybeDeleteCookie(cookieName, null, path, doc);\n",
L"    }\n",
L"};\n",
L"var _recursivelyDeleteCookie = function(cookieName, domain, path, doc) {\n",
L"    var slashIndex = path.lastIndexOf('/');\n",
L"    var finalIndex = path.length-1;\n",
L"    if (slashIndex == finalIndex) {\n",
L"        slashIndex--;\n",
L"    }\n",
L"    if (slashIndex != -1) {\n",
L"        deleted = _recursivelyDeleteCookie(cookieName, domain, path.substring(0, slashIndex+1), doc);\n",
L"    }\n",
L"    return _recursivelyDeleteCookieDomains(cookieName, domain, path, doc);\n",
L"};\n",
L"var recursivelyDeleteCookie = function(cookieName, domain, path, win) {\n",
L"    if (!win) win = window;\n",
L"    var doc = win.document;\n",
L"    if (!domain) {\n",
L"        domain = doc.domain;\n",
L"    }\n",
L"    if (!path) {\n",
L"        path = win.location.pathname;\n",
L"    }\n",
L"    var deleted = _recursivelyDeleteCookie(cookieName, '.' + domain, path, doc);\n",
L"    // Finally try a null path (Try it last because it's uncommon)\n",
L"    deleted = _recursivelyDeleteCookieDomains(cookieName, '.' + domain, null, doc);\n",
L"};\n",
L"recursivelyDeleteCookie(arguments[0]);\n",
L"};})();\n",
NULL
};
