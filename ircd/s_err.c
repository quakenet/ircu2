/*
 * IRC - Internet Relay Chat, ircd/s_err.c
 * Copyright (C) 1992 Darren Reed
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 1, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id$
 */
#include "config.h"

#include "numeric.h"
#include "s_debug.h"

#include <assert.h>
#include <string.h>

static Numeric replyTable[] = {
/* 000 */
  { 0 },
/* 001 */
  { RPL_WELCOME, ":Welcome to the %s IRC Network%s%s, %s", "001" },
/* 002 */
  { RPL_YOURHOST, ":Your host is %s, running version %s", "002" },
/* 003 */
  { RPL_CREATED, ":This server was created %s", "003" },
/* 004 */
  { RPL_MYINFO, "%s %s %s %s %s", "004" },
/* 005 */
  { RPL_ISUPPORT, "%s :are supported by this server", "005" },
/* 006 */
  { 0 },
/* 007 */
  { 0 },
/* 008 */
  { RPL_SNOMASK, "%d :: Server notice mask (%#x)", "008" },
/* 009 */
  { RPL_STATMEMTOT, "%u %u :Bytes Blocks", "009" },
/* 010 */
#ifdef MEMSIZESTATS
  { RPL_STATMEM, "%u %u %s %u", "010" },
#else
  { RPL_STATMEM, "%u %u %s", "010" },
#endif
/* 011 */
  { 0 },
/* 012 */
  { 0 },
/* 013 */
  { 0 },
/* 014 */
  { 0 },
/* 015 */
  { RPL_MAP, ":%s%s%s %s [%i clients]", "015" },
/* 016 */
  { RPL_MAPMORE, ":%s%s --> *more*", "016" },
/* 017 */
  { RPL_MAPEND, ":End of /MAP", "017" },
/* 018 */
  { 0 },
/* 019 */
  { 0 },
/* 020 */
  { 0 },
/* 021 */
  { 0 },
/* 022 */
  { 0 },
/* 023 */
  { 0 },
/* 024 */
  { 0 },
/* 025 */
  { 0 },
/* 026 */
  { 0 },
/* 027 */
  { 0 },
/* 028 */
  { 0 },
/* 029 */
  { 0 },
/* 030 */
  { RPL_APASSWARN, ":%s%s%s%s%s", "030" },
/* 031 */
  { 0 },
/* 032 */
  { 0 },
/* 033 */
  { 0 },
/* 034 */
  { 0 },
/* 035 */
  { 0 },
/* 036 */
  { 0 },
/* 037 */
  { 0 },
/* 038 */
  { 0 },
/* 039 */
  { 0 },
/* 040 */
  { 0 },
/* 041 */
  { 0 },
/* 042 */
  { 0 },
/* 043 */
  { 0 },
/* 044 */
  { 0 },
/* 045 */
  { 0 },
/* 046 */
  { 0 },
/* 047 */
  { 0 },
/* 048 */
  { 0 },
/* 049 */
  { 0 },
/* 050 */
  { 0 },
/* 051 */
  { 0 },
/* 052 */
  { 0 },
/* 053 */
  { 0 },
/* 054 */
  { 0 },
/* 055 */
  { 0 },
/* 056 */
  { 0 },
/* 057 */
  { 0 },
/* 058 */
  { 0 },
/* 059 */
  { 0 },
/* 060 */
  { 0 },
/* 061 */
  { 0 },
/* 062 */
  { 0 },
/* 063 */
  { 0 },
/* 064 */
  { 0 },
/* 065 */
  { 0 },
/* 066 */
  { 0 },
/* 067 */
  { 0 },
/* 068 */
  { 0 },
/* 069 */
  { 0 },
/* 070 */
  { 0 },
/* 071 */
  { 0 },
/* 072 */
  { 0 },
/* 073 */
  { 0 },
/* 074 */
  { 0 },
/* 075 */
  { 0 },
/* 076 */
  { 0 },
/* 077 */
  { 0 },
/* 078 */
  { 0 },
/* 079 */
  { 0 },
/* 080 */
  { 0 },
/* 081 */
  { 0 },
/* 082 */
  { 0 },
/* 083 */
  { 0 },
/* 084 */
  { 0 },
/* 085 */
  { 0 },
/* 086 */
  { 0 },
/* 087 */
  { 0 },
/* 088 */
  { 0 },
/* 089 */
  { 0 },
/* 090 */
  { 0 },
/* 091 */
  { 0 },
/* 092 */
  { 0 },
/* 093 */
  { 0 },
/* 094 */
  { 0 },
/* 095 */
  { 0 },
/* 096 */
  { 0 },
/* 097 */
  { 0 },
/* 098 */
  { 0 },
/* 099 */
  { 0 },
/* 100 */
  { 0 },
/* 101 */
  { 0 },
/* 102 */
  { 0 },
/* 103 */
  { 0 },
/* 104 */
  { 0 },
/* 105 */
  { 0 },
/* 106 */
  { 0 },
/* 107 */
  { 0 },
/* 108 */
  { 0 },
/* 109 */
  { 0 },
/* 110 */
  { 0 },
/* 111 */
  { 0 },
/* 112 */
  { 0 },
/* 113 */
  { 0 },
/* 114 */
  { 0 },
/* 115 */
  { 0 },
/* 116 */
  { 0 },
/* 117 */
  { 0 },
/* 118 */
  { 0 },
/* 119 */
  { 0 },
/* 120 */
  { 0 },
/* 121 */
  { 0 },
/* 122 */
  { 0 },
/* 123 */
  { 0 },
/* 124 */
  { 0 },
/* 125 */
  { 0 },
/* 126 */
  { 0 },
/* 127 */
  { 0 },
/* 128 */
  { 0 },
/* 129 */
  { 0 },
/* 130 */
  { 0 },
/* 131 */
  { 0 },
/* 132 */
  { 0 },
/* 133 */
  { 0 },
/* 134 */
  { 0 },
/* 135 */
  { 0 },
/* 136 */
  { 0 },
/* 137 */
  { 0 },
/* 138 */
  { 0 },
/* 139 */
  { 0 },
/* 140 */
  { 0 },
/* 141 */
  { 0 },
/* 142 */
  { 0 },
/* 143 */
  { 0 },
/* 144 */
  { 0 },
/* 145 */
  { 0 },
/* 146 */
  { 0 },
/* 147 */
  { 0 },
/* 148 */
  { 0 },
/* 149 */
  { 0 },
/* 150 */
  { 0 },
/* 151 */
  { 0 },
/* 152 */
  { 0 },
/* 153 */
  { 0 },
/* 154 */
  { 0 },
/* 155 */
  { 0 },
/* 156 */
  { 0 },
/* 157 */
  { 0 },
/* 158 */
  { 0 },
/* 159 */
  { 0 },
/* 160 */
  { 0 },
/* 161 */
  { 0 },
/* 162 */
  { 0 },
/* 163 */
  { 0 },
/* 164 */
  { 0 },
/* 165 */
  { 0 },
/* 166 */
  { 0 },
/* 167 */
  { 0 },
/* 168 */
  { 0 },
/* 169 */
  { 0 },
/* 170 */
  { 0 },
/* 171 */
  { 0 },
/* 172 */
  { 0 },
/* 173 */
  { 0 },
/* 174 */
  { 0 },
/* 175 */
  { 0 },
/* 176 */
  { 0 },
/* 177 */
  { 0 },
/* 178 */
  { 0 },
/* 179 */
  { 0 },
/* 180 */
  { 0 },
/* 181 */
  { 0 },
/* 182 */
  { 0 },
/* 183 */
  { 0 },
/* 184 */
  { 0 },
/* 185 */
  { 0 },
/* 186 */
  { 0 },
/* 187 */
  { 0 },
/* 188 */
  { 0 },
/* 189 */
  { 0 },
/* 190 */
  { 0 },
/* 191 */
  { 0 },
/* 192 */
  { 0 },
/* 193 */
  { 0 },
/* 194 */
  { 0 },
/* 195 */
  { 0 },
/* 196 */
  { 0 },
/* 197 */
  { 0 },
/* 198 */
  { 0 },
/* 199 */
  { 0 },
/* 200 */
  { RPL_TRACELINK, "Link %s.%s %s %s", "200" },
/* 201 */
  { RPL_TRACECONNECTING, "Try. %s %s", "201" },
/* 202 */
  { RPL_TRACEHANDSHAKE, "H.S. %s %s", "202" },
/* 203 */
  { RPL_TRACEUNKNOWN, "???? %s %s", "203" },
/* 204 */
  { RPL_TRACEOPERATOR, "Oper %s %s %ld", "204" },
/* 205 */
  { RPL_TRACEUSER, "User %s %s %ld", "205" },
/* 206 */
  { RPL_TRACESERVER, "Serv %s %dS %dC %s %s!%s@%s %ld %ld", "206" },
/* 207 */
  { 0 },
/* 208 */
  { RPL_TRACENEWTYPE, "<newtype> 0 %s", "208" },
/* 209 */
  { RPL_TRACECLASS, "Class %s %d", "209" },
/* 210 */
  { 0 },
/* 211 */
  { RPL_STATSLINKINFO, 0, "211" },
/* 212 */
  { RPL_STATSCOMMANDS, "%s %u %u", "212" },
/* 213 */
  { RPL_STATSCLINE, "%c %s * %s %d %s", "213" },
/* 214 */
  { RPL_STATSNLINE, "%c %s * %s %d %d", "214" },
/* 215 */
  { RPL_STATSILINE, "%c %s %s %s %d %s", "215" },
/* 216 */
  { RPL_STATSKLINE, "%c %s \"%s\" %s 0 0", "216" },
/* 217 */
  { RPL_STATSPLINE, "P %d %d %s %s", "217" },
/* 218 */
  { RPL_STATSYLINE, "%c %s %d %d %d %ld %d", "218" },
/* 219 */
  { RPL_ENDOFSTATS, "%c :End of /STATS report", "219" },
/* 220 */
  { 0 },
/* 221 */
  { RPL_UMODEIS, "%s", "221" },
/* 222 */
  { 0 },
/* 223 */
  { 0 },
/* 224 */
  { 0 },
/* 225 */
  { 0 },
/* 226 */
  { 0 },
/* 227 */
  { 0 },
/* 228 */
  { RPL_STATSQLINE, "Q %s :%s", "228" },
/* 229 */
  { 0 },
/* 230 */
  { 0 },
/* 231 */
  { RPL_SERVICEINFO, 0, "231" },
/* 232 */
  { RPL_ENDOFSERVICES, 0, "232" },
/* 233 */
  { RPL_SERVICE, 0, "233" },
/* 234 */
  { RPL_SERVLIST, 0, "234" },
/* 235 */
  { RPL_SERVLISTEND, 0, "235" },
/* 236 */
  { RPL_STATSVERBOSE, "V :Sent as explicit", "236" },
/* 237 */
  { RPL_STATSENGINE, "%s :Event loop engine", "237" },
/* 238 */
  { RPL_STATSFLINE, "%c %s %s", "238" },
/* 239 */
  { 0 },
/* 240 */
  { 0 },
/* 241 */
  { RPL_STATSLLINE, "%c %s * %s %d %d", "241" },
/* 242 */
  { RPL_STATSUPTIME, ":Server Up %d days, %d:%02d:%02d", "242" },
/* 243 */
  { RPL_STATSOLINE, "%c %s * %s %d %d", "243" },
/* 244 */
  { RPL_STATSHLINE, "%c %s * %s %d %d", "244" },
/* 245 */
  { 0 },
/* 246 */
  { RPL_STATSTLINE, "%c %s %s", "246" },
/* 247 */
  { RPL_STATSGLINE, "%c %s@%s %Tu :%s", "247" },
/* 248 */
  { RPL_STATSULINE, "%c %s %s %s %d %d", "248" },
/* 249 */
  { RPL_STATSDEBUG, 0, "249" },
/* 250 */
  { RPL_STATSCONN, ":Highest connection count: %d (%d clients)", "250" },
/* 251 */
  { RPL_LUSERCLIENT, ":There are %d users and %d invisible on %d servers", "251" },
/* 252 */
  { RPL_LUSEROP, "%d :operator(s) online", "252" },
/* 253 */
  { RPL_LUSERUNKNOWN, "%d :unknown connection(s)", "253" },
/* 254 */
  { RPL_LUSERCHANNELS, "%d :channels formed", "254" },
/* 255 */
  { RPL_LUSERME, ":I have %d clients and %d servers", "255" },
/* 256 */
  { RPL_ADMINME, ":Administrative info about %s", "256" },
/* 257 */
  { RPL_ADMINLOC1, ":%s", "257" },
/* 258 */
  { RPL_ADMINLOC2, ":%s", "258" },
/* 259 */
  { RPL_ADMINEMAIL, ":%s", "259" },
/* 260 */
  { 0 },
/* 261 */
  { RPL_TRACELOG, "File %s %d", "261" },
/* 262 */
  { RPL_TRACEPING, "Ping %s %s", "262" },
/* 263 */
  { 0 },
/* 264 */
  { 0 },
/* 265 */
  { 0 },
/* 266 */
  { 0 },
/* 267 */
  { 0 },
/* 268 */
  { 0 },
/* 269 */
  { 0 },
/* 270 */
  { RPL_PRIVS, "%s :", "270" },
/* 271 */
  { RPL_SILELIST, "%s %s", "271" },
/* 272 */
  { RPL_ENDOFSILELIST, "%s :End of Silence List", "272" },
/* 273 */
  { 0 },
/* 274 */
  { 0 },
/* 275 */
  { RPL_STATSDLINE, "%c %s %s", "275" },
/* 276 */
  { RPL_STATSRLINE, "%-9s %-9s %-10s %s", "276" },
/* 277 */
  { 0 },
/* 278 */
  { 0 },
/* 279 */
  { 0 },
/* 280 */
  { RPL_GLIST, "%s%s%s %Tu %s %c :%s", "280" },
/* 281 */
  { RPL_ENDOFGLIST, ":End of G-line List", "281" },
/* 282 */
  { RPL_JUPELIST, "%s %Tu %s %c :%s", "282" },
/* 283 */
  { RPL_ENDOFJUPELIST, ":End of Jupe List", "283" },
/* 284 */
  { RPL_FEATURE, 0, "284" },
/* 285 */
  { 0 },
/* 286 */
  { 0 },
/* 287 */
  { 0 },
/* 288 */
  { 0 },
/* 289 */
  { 0 },
/* 290 */
  { 0 },
/* 291 */
  { 0 },
/* 292 */
  { 0 },
/* 293 */
  { 0 },
/* 294 */
  { 0 },
/* 295 */
  { 0 },
/* 296 */
  { 0 },
/* 297 */
  { 0 },
/* 298 */
  { 0 },
/* 299 */
  { 0 },
/* 300 */
  { RPL_NONE, 0, "300" },
/* 301 */
  { RPL_AWAY, "%s :%s", "301" },
/* 302 */
  { RPL_USERHOST, ":", "302" },
/* 303 */
  { RPL_ISON, ":", "303" },
/* 304 */
  { RPL_TEXT, 0, "304" },
/* 305 */
  { RPL_UNAWAY, ":You are no longer marked as being away", "305" },
/* 306 */
  { RPL_NOWAWAY, ":You have been marked as being away", "306" },
/* 307 */
  { 0 },
/* 308 */
  { 0 },
/* 309 */
  { 0 },
/* 310 */
  { 0 },
/* 311 */
  { RPL_WHOISUSER, "%s %s %s * :%s", "311" },
/* 312 */
  { RPL_WHOISSERVER, "%s %s :%s", "312" },
/* 313 */
  { RPL_WHOISOPERATOR, "%s :is an IRC Operator", "313" },
/* 314 */
  { RPL_WHOWASUSER, "%s %s %s * :%s", "314" },
/* 315 */
  { RPL_ENDOFWHO, "%s :End of /WHO list.", "315" },
/* 316 */
  { 0 },
/* 317 */
  { RPL_WHOISIDLE, "%s %ld %ld :seconds idle, signon time", "317" },
/* 318 */
  { RPL_ENDOFWHOIS, "%s :End of /WHOIS list.", "318" },
/* 319 */
  { RPL_WHOISCHANNELS, "%s :%s", "319" },
/* 320 */
  { 0 },
/* 321 */
  { RPL_LISTSTART, "Channel :Users  Name", "321" },
/* 322 */
  { RPL_LIST, "%s %d :%s", "322" },
/* 323 */
  { RPL_LISTEND, ":End of /LIST", "323" },
/* 324 */
  { RPL_CHANNELMODEIS, "%s %s %s", "324" },
/* 325 */
  { 0 },
/* 326 */
  { 0 },
/* 327 */
  { 0 },
/* 328 */
  { 0 },
/* 329 */
  { RPL_CREATIONTIME, "%s %Tu", "329" },
/* 330 */
  { RPL_WHOISACCOUNT, "%s %s :is logged in as", "330" },
/* 331 */
  { RPL_NOTOPIC, "%s :No topic is set.", "331" },
/* 332 */
  { RPL_TOPIC, "%s :%s", "332" },
/* 333 */
  { RPL_TOPICWHOTIME, "%s %s %Tu", "333" },
/* 334 */
  { RPL_LISTUSAGE, ":%s", "334" },
/* 335 */
  { 0 },
/* 336 */
  { 0 },
/* 337 */
  { 0 },
/* 338 */
  { RPL_WHOISACTUALLY, "%s %s@%s %s :Actual user@host, Actual IP", "338" },
/* 339 */
  { 0 },
/* 340 */
  { RPL_USERIP, ":", "340" },
/* 341 */
  { RPL_INVITING, "%s %s", "341" },
/* 342 */
  { 0 },
/* 343 */
  { 0 },
/* 344 */
  { 0 },
/* 345 */
  { 0 },
/* 346 */
  { RPL_INVITELIST, ":%s", "346" },
/* 347 */
  { RPL_ENDOFINVITELIST, ":End of Invite List", "347" },
/* 348 */
  { 0 },
/* 349 */
  { 0 },
/* 350 */
  { 0 },
/* 351 */
  { RPL_VERSION, "%s.%s %s :%s", "351" },
/* 352 */
  { RPL_WHOREPLY, "%s", "352" },
/* 353 */
  { RPL_NAMREPLY, "%s", "353" },
/* 354 */
  { RPL_WHOSPCRPL, "%s", "354" },
/* 355 */
  { RPL_DELNAMREPLY, "%s", "355" },
/* 356 */
  { 0 },
/* 357 */
  { 0 },
/* 358 */
  { 0 },
/* 359 */
  { 0 },
/* 360 */
  { 0 },
/* 361 */
  { RPL_KILLDONE, 0, "361" }, /* Not used */
/* 362 */
  { RPL_CLOSING, "%s :Operator enforced Close", "362" },
/* 363 */
  { RPL_CLOSEEND, "%d :Connections Closed", "363" },
/* 364 */
  { RPL_LINKS, "%s %s :%d P%u %s", "364" },
/* 365 */
  { RPL_ENDOFLINKS, "%s :End of /LINKS list.", "365" },
/* 366 */
  { RPL_ENDOFNAMES, "%s :End of /NAMES list.", "366" },
/* 367 */
  { RPL_BANLIST, "%s %s %s %Tu", "367" },
/* 368 */
  { RPL_ENDOFBANLIST, "%s :End of Channel Ban List", "368" },
/* 369 */
  { RPL_ENDOFWHOWAS, "%s :End of WHOWAS", "369" },
/* 370 */
  { 0 },
/* 371 */
  { RPL_INFO, ":%s", "371" },
/* 372 */
  { RPL_MOTD, ":- %s", "372" },
/* 373 */
  { RPL_INFOSTART, ":Server INFO", "373" },
/* 374 */
  { RPL_ENDOFINFO, ":End of /INFO list.", "374" },
/* 375 */
  { RPL_MOTDSTART, ":- %s Message of the Day - ", "375" },
/* 376 */
  { RPL_ENDOFMOTD, ":End of /MOTD command.", "376" },
/* 377 */
  { 0 },
/* 378 */
  { 0 },
/* 379 */
  { 0 },
/* 380 */
  { 0 },
/* 381 */
  { RPL_YOUREOPER, ":You are now an IRC Operator", "381" },
/* 382 */
  { RPL_REHASHING, "%s :Rehashing", "382" },
/* 383 */
  { 0 },
/* 384 */
  { RPL_MYPORTIS, "%d :Port to local server is", "384" }, /* not used */
/* 385 */
  { RPL_NOTOPERANYMORE, 0, "385" }, /* not used */
/* 386 */
  { 0 },
/* 387 */
  { 0 },
/* 388 */
  { 0 },
/* 389 */
  { 0 },
/* 390 */
  { 0 },
/* 391 */
  { RPL_TIME, "%s %Tu %ld :%s", "391" },
/* 392 */
  { 0 },
/* 393 */
  { 0 },
/* 394 */
  { 0 },
/* 395 */
  { 0 },
/* 396 */
  { RPL_HOSTHIDDEN, "%s :is now your hidden host", "396" },
/* 397 */
  { 0 },
/* 398 */
  { 0 },
/* 399 */
  { 0 },
/* 400 */
  { ERR_FIRSTERROR, "", "400" },
/* 401 */
  { ERR_NOSUCHNICK, "%s :No such nick", "401" },
/* 402 */
  { ERR_NOSUCHSERVER, "%s :No such server", "402" },
/* 403 */
  { ERR_NOSUCHCHANNEL, "%s :No such channel", "403" },
/* 404 */
  { ERR_CANNOTSENDTOCHAN, "%s :Cannot send to channel", "404" },
/* 405 */
  { ERR_TOOMANYCHANNELS, "%s :You have joined too many channels", "405" },
/* 406 */
  { ERR_WASNOSUCHNICK, "%s :There was no such nickname", "406" },
/* 407 */
  { ERR_TOOMANYTARGETS, "%s :Duplicate recipients. No message delivered", "407" },
/* 408 */
  { 0 },
/* 409 */
  { ERR_NOORIGIN, ":No origin specified", "409" },
/* 410 */
  { 0 },
/* 411 */
  { ERR_NORECIPIENT, ":No recipient given (%s)", "411" },
/* 412 */
  { ERR_NOTEXTTOSEND, ":No text to send", "412" },
/* 413 */
  { ERR_NOTOPLEVEL, "%s :No toplevel domain specified", "413" },
/* 414 */
  { ERR_WILDTOPLEVEL, "%s :Wildcard in toplevel Domain", "414" },
/* 415 */
  { 0 },
/* 416 */
  { ERR_QUERYTOOLONG, "%s :Too many lines in the output, restrict your query", "416" },
/* 417 */
  { 0 },
/* 418 */
  { 0 },
/* 419 */
  { 0 },
/* 420 */
  { 0 },
/* 421 */
  { ERR_UNKNOWNCOMMAND, "%s :Unknown command", "421" },
/* 422 */
  { ERR_NOMOTD, ":MOTD File is missing", "422" },
/* 423 */
  { ERR_NOADMININFO, "%s :No administrative info available", "423" },
/* 424 */
  { 0 },
/* 425 */
  { 0 },
/* 426 */
  { 0 },
/* 427 */
  { 0 },
/* 428 */
  { 0 },
/* 429 */
  { 0 },
/* 430 */
  { 0 },
/* 431 */
  { ERR_NONICKNAMEGIVEN, ":No nickname given", "431" },
/* 432 */
  { ERR_ERRONEUSNICKNAME, "%s :Erroneous Nickname", "432" },
/* 433 */
  { ERR_NICKNAMEINUSE, "%s :Nickname is already in use.", "433" },
/* 434 */
  { 0 },
/* 435 */
  { 0 },
/* 436 */
  { ERR_NICKCOLLISION, "%s :Nickname collision KILL", "436" },
/* 437 */
  { ERR_BANNICKCHANGE, "%s :Cannot change nickname while banned on channel or channel is moderated", "437" },
/* 438 */
  { ERR_NICKTOOFAST, "%s :Nick change too fast. Please wait %d seconds.", "438" },
/* 439 */
  { ERR_TARGETTOOFAST, "%s :Target change too fast. Please wait %d seconds.", "439" },
/* 440 */
  { ERR_SERVICESDOWN, "%s :Services are currently unavailable.", "440" },
/* 441 */
  { ERR_USERNOTINCHANNEL, "%s %s :They aren't on that channel", "441" },
/* 442 */
  { ERR_NOTONCHANNEL, "%s :You're not on that channel", "442" },
/* 443 */
  { ERR_USERONCHANNEL, "%s %s :is already on channel", "443" },
/* 444 */
  { 0 },
/* 445 */
  { 0 },
/* 446 */
  { 0 },
/* 447 */
  { 0 },
/* 448 */
  { 0 },
/* 449 */
  { 0 },
/* 450 */
  { 0 },
/* 451 */
  { ERR_NOTREGISTERED, ":You have not registered", "451" },
/* 452 */
  { 0 },
/* 453 */
  { 0 },
/* 454 */
  { 0 },
/* 455 */
  { 0 },
/* 456 */
  { 0 },
/* 457 */
  { 0 },
/* 458 */
  { 0 },
/* 459 */
  { 0 },
/* 460 */
  { 0 },
/* 461 */
  { ERR_NEEDMOREPARAMS, "%s :Not enough parameters", "461" },
/* 462 */
  { ERR_ALREADYREGISTRED, ":You may not reregister", "462" },
/* 463 */
  { ERR_NOPERMFORHOST, ":Your host isn't among the privileged", "463" },
/* 464 */
  { ERR_PASSWDMISMATCH, ":Password Incorrect", "464" },
/* 465 */
  { ERR_YOUREBANNEDCREEP, ":You are banned from this server", "465" },
/* 466 */
  { ERR_YOUWILLBEBANNED, "", "466" },
/* 467 */
  { ERR_KEYSET, "%s :Channel key already set", "467" },
/* 468 */
  { ERR_INVALIDUSERNAME, 0, "468" },
/* 469 */
  { 0 },
/* 470 */
  { 0 },
/* 471 */
  { ERR_CHANNELISFULL, "%s :Cannot join channel (+l)", "471" },
/* 472 */
  { ERR_UNKNOWNMODE, "%c :is unknown mode char to me", "472" },
/* 473 */
  { ERR_INVITEONLYCHAN, "%s :Cannot join channel (+i)", "473" },
/* 474 */
  { ERR_BANNEDFROMCHAN, "%s :Cannot join channel (+b)", "474" },
/* 475 */
  { ERR_BADCHANNELKEY, "%s :Cannot join channel (+k)", "475" },
/* 476 */
  { ERR_BADCHANMASK, "%s :Bad Channel Mask", "476" },
/* 477 */
  { ERR_NEEDREGGEDNICK, "%s :Cannot join channel (+r)", "477" },
/* 478 */
  { ERR_BANLISTFULL, "%s %s :Channel ban/ignore list is full", "478" },
/* 479 */
  { ERR_BADCHANNAME, "%s :Cannot join channel (access denied on this server)", "479" },
/* 480 */
  { 0 },
/* 481 */
  { ERR_NOPRIVILEGES, ":Permission Denied: Insufficient privileges", "481" },
/* 482 */
  { ERR_CHANOPRIVSNEEDED, "%s :You're not channel operator", "482" },
/* 483 */
  { ERR_CANTKILLSERVER, ":You cant kill a server!", "483" },
/* 484 */
  { ERR_ISCHANSERVICE, "%s %s :Cannot kill, kick or deop a network service", "484" },
/* 485 */
  { 0 },
/* 486 */
  { 0 },
/* 487 */
  { 0 },
/* 488 */
  { 0 },
/* 489 */
  { ERR_VOICENEEDED, "%s :You're neither voiced nor channel operator", "489" },
/* 490 */
  { 0 },
/* 491 */
  { ERR_NOOPERHOST, ":No O-lines for your host", "491" },
/* 492 */
  { 0 },
/* 493 */
  { ERR_NOFEATURE, "%s :No such feature", "493" },
/* 494 */
  { ERR_BADFEATVALUE, "%s :Bad value for feature %s", "494" },
/* 495 */
  { ERR_BADLOGTYPE, "%s :No such log type", "495" },
/* 496 */
  { ERR_BADLOGSYS, "%s :No such log subsystem", "496" },
/* 497 */
  { ERR_BADLOGVALUE, "%s :Bad value for log type", "497" },
/* 498 */
  { ERR_ISOPERLCHAN, "%s %s :Cannot kick or deop an IRC Operator on a local channel", "498" },
/* 499 */
  { 0 },
/* 500 */
  { 0 },
/* 501 */
  { ERR_UMODEUNKNOWNFLAG, "%c :Unknown user MODE flag", "501" },
/* 502 */
  { ERR_USERSDONTMATCH, ":Cant change mode for other users", "502" },
/* 503 */
  { 0 },
/* 504 */
  { 0 },
/* 505 */
  { 0 },
/* 506 */
  { 0 },
/* 507 */
  { 0 },
/* 508 */
  { 0 },
/* 509 */
  { 0 },
/* 510 */
  { 0 },
/* 511 */
  { ERR_SILELISTFULL, "%s :Your silence list is full", "511" },
/* 512 */
  { ERR_NOSUCHGLINE, "%s :No such gline", "512" },
/* 513 */
  { ERR_BADPING, 0, "513" },
/* 514 */
  { ERR_NOSUCHJUPE, "%s :No such jupe", "514" },
/* 515 */
  { ERR_BADEXPIRE, "%Tu :Bad expire time", "515" },
/* 516 */
  { ERR_DONTCHEAT, " :Don't Cheat.", "516" },
/* 517 */
  { ERR_DISABLED, "%s :Command disabled.", "517" },
/* 518 */
  { ERR_LONGMASK, " :Mask is too long", "518" },
/* 519 */
  { ERR_TOOMANYUSERS, "%d :Too many users affected by mask", "519" },
/* 520 */
  { ERR_MASKTOOWIDE, "%s :Mask is too wide", "520" },
/* 521 */
  { 0 },
/* 522 */
  { 0 },
/* 523 */
  { 0 },
/* 524 */
  { ERR_QUARANTINED, "%s :Channel is quarantined : %s", "524" },
/* 525 */
  { 0 },
/* 526 */
  { 0 },
/* 527 */
  { 0 },
/* 528 */
  { 0 },
/* 529 */
  { 0 },
/* 530 */
  { 0 },
/* 531 */
  { 0 },
/* 532 */
  { 0 },
/* 533 */
  { 0 },
/* 534 */
  { 0 },
/* 535 */
  { 0 },
/* 536 */
  { 0 },
/* 537 */
  { 0 },
/* 538 */
  { 0 },
/* 539 */
  { 0 },
/* 540 */
  { 0 },
/* 541 */
  { 0 },
/* 542 */
  { 0 },
/* 543 */
  { 0 },
/* 544 */
  { 0 },
/* 545 */
  { 0 },
/* 546 */
  { 0 },
/* 547 */
  { 0 },
/* 548 */
  { 0 },
/* 549 */
  { 0 },
/* 550 */
  { ERR_NOTLOWEROPLEVEL, "%s %s %hu %hu :Cannot %s someone with %s op-level", "550" },
/* 551 */
  { ERR_NOTMANAGER, "%s :You must be channel Admin to add or remove a password. %s %s %s", "551" },
/* 552 */
  { ERR_CHANSECURED, "%s :Channel is older than 48 hours and secured. Cannot change Admin pass anymore", "552" },
/* 553 */
  { ERR_UPASSSET, "%s :Cannot remove Admin pass (+A) while User pass (+u) is still set.  First use /MODE %s -u <userpass>", "553" },
/* 554 */
  { ERR_UPASSNOTSET, "%s :Cannot set user pass (+u) while Admin pass (+A) is not set.  First use /MODE %s +A <adminpass>", "554" },
/* 555 */
  { 0 },
/* 556 */
  { 0 },
/* 557 */
  { 0 },
/* 558 */
  { 0 },
/* 559 */
  { 0 },
/* 560 */
  { 0 },
/* 561 */
  { 0 },
/* 562 */
  { 0 },
/* 563 */
  { 0 },
/* 564 */
  { 0 },
/* 565 */
  { 0 },
/* 566 */
  { 0 },
/* 567 */
  { 0 },
/* 568 */
  { 0 },
/* 569 */
  { 0 },
/* 570 */
  { 0 },
/* 571 */
  { 0 },
/* 572 */
  { 0 },
/* 573 */
  { 0 },
/* 574 */
  { 0 },
/* 575 */
  { 0 },
/* 576 */
  { 0 },
/* 577 */
  { 0 },
/* 578 */
  { 0 },
/* 579 */
  { 0 },
/* 580 */
  { 0 },
/* 581 */
  { 0 },
/* 582 */
  { 0 },
/* 583 */
  { 0 },
/* 584 */
  { 0 },
/* 585 */
  { 0 },
/* 586 */
  { 0 },
/* 587 */
  { 0 },
/* 588 */
  { 0 },
/* 589 */
  { 0 },
/* 590 */
  { 0 },
/* 591 */
  { 0 },
/* 592 */
  { 0 },
/* 593 */
  { 0 },
/* 594 */
  { 0 },
/* 595 */
  { 0 },
/* 596 */
  { 0 },
/* 597 */
  { 0 },
/* 598 */
  { 0 },
/* 599 */
  { 0 }
};

const struct Numeric* get_error_numeric(int n)
{
  assert(0 < n);
  assert(n < ERR_LASTERROR);
  assert(0 != replyTable[n].value);

  return &replyTable[n];
}

static char numbuff[512];

/* *INDENT-OFF* */

static const char atoi_tab[4000] = {
    '0','0','0',0, '0','0','1',0, '0','0','2',0, '0','0','3',0, '0','0','4',0,
    '0','0','5',0, '0','0','6',0, '0','0','7',0, '0','0','8',0, '0','0','9',0,
    '0','1','0',0, '0','1','1',0, '0','1','2',0, '0','1','3',0, '0','1','4',0,
    '0','1','5',0, '0','1','6',0, '0','1','7',0, '0','1','8',0, '0','1','9',0,
    '0','2','0',0, '0','2','1',0, '0','2','2',0, '0','2','3',0, '0','2','4',0,
    '0','2','5',0, '0','2','6',0, '0','2','7',0, '0','2','8',0, '0','2','9',0,
    '0','3','0',0, '0','3','1',0, '0','3','2',0, '0','3','3',0, '0','3','4',0,
    '0','3','5',0, '0','3','6',0, '0','3','7',0, '0','3','8',0, '0','3','9',0,
    '0','4','0',0, '0','4','1',0, '0','4','2',0, '0','4','3',0, '0','4','4',0,
    '0','4','5',0, '0','4','6',0, '0','4','7',0, '0','4','8',0, '0','4','9',0,
    '0','5','0',0, '0','5','1',0, '0','5','2',0, '0','5','3',0, '0','5','4',0,
    '0','5','5',0, '0','5','6',0, '0','5','7',0, '0','5','8',0, '0','5','9',0,
    '0','6','0',0, '0','6','1',0, '0','6','2',0, '0','6','3',0, '0','6','4',0,
    '0','6','5',0, '0','6','6',0, '0','6','7',0, '0','6','8',0, '0','6','9',0,
    '0','7','0',0, '0','7','1',0, '0','7','2',0, '0','7','3',0, '0','7','4',0,
    '0','7','5',0, '0','7','6',0, '0','7','7',0, '0','7','8',0, '0','7','9',0,
    '0','8','0',0, '0','8','1',0, '0','8','2',0, '0','8','3',0, '0','8','4',0,
    '0','8','5',0, '0','8','6',0, '0','8','7',0, '0','8','8',0, '0','8','9',0,
    '0','9','0',0, '0','9','1',0, '0','9','2',0, '0','9','3',0, '0','9','4',0,
    '0','9','5',0, '0','9','6',0, '0','9','7',0, '0','9','8',0, '0','9','9',0,
    '1','0','0',0, '1','0','1',0, '1','0','2',0, '1','0','3',0, '1','0','4',0,
    '1','0','5',0, '1','0','6',0, '1','0','7',0, '1','0','8',0, '1','0','9',0,
    '1','1','0',0, '1','1','1',0, '1','1','2',0, '1','1','3',0, '1','1','4',0,
    '1','1','5',0, '1','1','6',0, '1','1','7',0, '1','1','8',0, '1','1','9',0,
    '1','2','0',0, '1','2','1',0, '1','2','2',0, '1','2','3',0, '1','2','4',0,
    '1','2','5',0, '1','2','6',0, '1','2','7',0, '1','2','8',0, '1','2','9',0,
    '1','3','0',0, '1','3','1',0, '1','3','2',0, '1','3','3',0, '1','3','4',0,
    '1','3','5',0, '1','3','6',0, '1','3','7',0, '1','3','8',0, '1','3','9',0,
    '1','4','0',0, '1','4','1',0, '1','4','2',0, '1','4','3',0, '1','4','4',0,
    '1','4','5',0, '1','4','6',0, '1','4','7',0, '1','4','8',0, '1','4','9',0,
    '1','5','0',0, '1','5','1',0, '1','5','2',0, '1','5','3',0, '1','5','4',0,
    '1','5','5',0, '1','5','6',0, '1','5','7',0, '1','5','8',0, '1','5','9',0,
    '1','6','0',0, '1','6','1',0, '1','6','2',0, '1','6','3',0, '1','6','4',0,
    '1','6','5',0, '1','6','6',0, '1','6','7',0, '1','6','8',0, '1','6','9',0,
    '1','7','0',0, '1','7','1',0, '1','7','2',0, '1','7','3',0, '1','7','4',0,
    '1','7','5',0, '1','7','6',0, '1','7','7',0, '1','7','8',0, '1','7','9',0,
    '1','8','0',0, '1','8','1',0, '1','8','2',0, '1','8','3',0, '1','8','4',0,
    '1','8','5',0, '1','8','6',0, '1','8','7',0, '1','8','8',0, '1','8','9',0,
    '1','9','0',0, '1','9','1',0, '1','9','2',0, '1','9','3',0, '1','9','4',0,
    '1','9','5',0, '1','9','6',0, '1','9','7',0, '1','9','8',0, '1','9','9',0,
    '2','0','0',0, '2','0','1',0, '2','0','2',0, '2','0','3',0, '2','0','4',0,
    '2','0','5',0, '2','0','6',0, '2','0','7',0, '2','0','8',0, '2','0','9',0,
    '2','1','0',0, '2','1','1',0, '2','1','2',0, '2','1','3',0, '2','1','4',0,
    '2','1','5',0, '2','1','6',0, '2','1','7',0, '2','1','8',0, '2','1','9',0,
    '2','2','0',0, '2','2','1',0, '2','2','2',0, '2','2','3',0, '2','2','4',0,
    '2','2','5',0, '2','2','6',0, '2','2','7',0, '2','2','8',0, '2','2','9',0,
    '2','3','0',0, '2','3','1',0, '2','3','2',0, '2','3','3',0, '2','3','4',0,
    '2','3','5',0, '2','3','6',0, '2','3','7',0, '2','3','8',0, '2','3','9',0,
    '2','4','0',0, '2','4','1',0, '2','4','2',0, '2','4','3',0, '2','4','4',0,
    '2','4','5',0, '2','4','6',0, '2','4','7',0, '2','4','8',0, '2','4','9',0,
    '2','5','0',0, '2','5','1',0, '2','5','2',0, '2','5','3',0, '2','5','4',0,
    '2','5','5',0, '2','5','6',0, '2','5','7',0, '2','5','8',0, '2','5','9',0,
    '2','6','0',0, '2','6','1',0, '2','6','2',0, '2','6','3',0, '2','6','4',0,
    '2','6','5',0, '2','6','6',0, '2','6','7',0, '2','6','8',0, '2','6','9',0,
    '2','7','0',0, '2','7','1',0, '2','7','2',0, '2','7','3',0, '2','7','4',0,
    '2','7','5',0, '2','7','6',0, '2','7','7',0, '2','7','8',0, '2','7','9',0,
    '2','8','0',0, '2','8','1',0, '2','8','2',0, '2','8','3',0, '2','8','4',0,
    '2','8','5',0, '2','8','6',0, '2','8','7',0, '2','8','8',0, '2','8','9',0,
    '2','9','0',0, '2','9','1',0, '2','9','2',0, '2','9','3',0, '2','9','4',0,
    '2','9','5',0, '2','9','6',0, '2','9','7',0, '2','9','8',0, '2','9','9',0,
    '3','0','0',0, '3','0','1',0, '3','0','2',0, '3','0','3',0, '3','0','4',0,
    '3','0','5',0, '3','0','6',0, '3','0','7',0, '3','0','8',0, '3','0','9',0,
    '3','1','0',0, '3','1','1',0, '3','1','2',0, '3','1','3',0, '3','1','4',0,
    '3','1','5',0, '3','1','6',0, '3','1','7',0, '3','1','8',0, '3','1','9',0,
    '3','2','0',0, '3','2','1',0, '3','2','2',0, '3','2','3',0, '3','2','4',0,
    '3','2','5',0, '3','2','6',0, '3','2','7',0, '3','2','8',0, '3','2','9',0,
    '3','3','0',0, '3','3','1',0, '3','3','2',0, '3','3','3',0, '3','3','4',0,
    '3','3','5',0, '3','3','6',0, '3','3','7',0, '3','3','8',0, '3','3','9',0,
    '3','4','0',0, '3','4','1',0, '3','4','2',0, '3','4','3',0, '3','4','4',0,
    '3','4','5',0, '3','4','6',0, '3','4','7',0, '3','4','8',0, '3','4','9',0,
    '3','5','0',0, '3','5','1',0, '3','5','2',0, '3','5','3',0, '3','5','4',0,
    '3','5','5',0, '3','5','6',0, '3','5','7',0, '3','5','8',0, '3','5','9',0,
    '3','6','0',0, '3','6','1',0, '3','6','2',0, '3','6','3',0, '3','6','4',0,
    '3','6','5',0, '3','6','6',0, '3','6','7',0, '3','6','8',0, '3','6','9',0,
    '3','7','0',0, '3','7','1',0, '3','7','2',0, '3','7','3',0, '3','7','4',0,
    '3','7','5',0, '3','7','6',0, '3','7','7',0, '3','7','8',0, '3','7','9',0,
    '3','8','0',0, '3','8','1',0, '3','8','2',0, '3','8','3',0, '3','8','4',0,
    '3','8','5',0, '3','8','6',0, '3','8','7',0, '3','8','8',0, '3','8','9',0,
    '3','9','0',0, '3','9','1',0, '3','9','2',0, '3','9','3',0, '3','9','4',0,
    '3','9','5',0, '3','9','6',0, '3','9','7',0, '3','9','8',0, '3','9','9',0,
    '4','0','0',0, '4','0','1',0, '4','0','2',0, '4','0','3',0, '4','0','4',0,
    '4','0','5',0, '4','0','6',0, '4','0','7',0, '4','0','8',0, '4','0','9',0,
    '4','1','0',0, '4','1','1',0, '4','1','2',0, '4','1','3',0, '4','1','4',0,
    '4','1','5',0, '4','1','6',0, '4','1','7',0, '4','1','8',0, '4','1','9',0,
    '4','2','0',0, '4','2','1',0, '4','2','2',0, '4','2','3',0, '4','2','4',0,
    '4','2','5',0, '4','2','6',0, '4','2','7',0, '4','2','8',0, '4','2','9',0,
    '4','3','0',0, '4','3','1',0, '4','3','2',0, '4','3','3',0, '4','3','4',0,
    '4','3','5',0, '4','3','6',0, '4','3','7',0, '4','3','8',0, '4','3','9',0,
    '4','4','0',0, '4','4','1',0, '4','4','2',0, '4','4','3',0, '4','4','4',0,
    '4','4','5',0, '4','4','6',0, '4','4','7',0, '4','4','8',0, '4','4','9',0,
    '4','5','0',0, '4','5','1',0, '4','5','2',0, '4','5','3',0, '4','5','4',0,
    '4','5','5',0, '4','5','6',0, '4','5','7',0, '4','5','8',0, '4','5','9',0,
    '4','6','0',0, '4','6','1',0, '4','6','2',0, '4','6','3',0, '4','6','4',0,
    '4','6','5',0, '4','6','6',0, '4','6','7',0, '4','6','8',0, '4','6','9',0,
    '4','7','0',0, '4','7','1',0, '4','7','2',0, '4','7','3',0, '4','7','4',0,
    '4','7','5',0, '4','7','6',0, '4','7','7',0, '4','7','8',0, '4','7','9',0,
    '4','8','0',0, '4','8','1',0, '4','8','2',0, '4','8','3',0, '4','8','4',0,
    '4','8','5',0, '4','8','6',0, '4','8','7',0, '4','8','8',0, '4','8','9',0,
    '4','9','0',0, '4','9','1',0, '4','9','2',0, '4','9','3',0, '4','9','4',0,
    '4','9','5',0, '4','9','6',0, '4','9','7',0, '4','9','8',0, '4','9','9',0,
    '5','0','0',0, '5','0','1',0, '5','0','2',0, '5','0','3',0, '5','0','4',0,
    '5','0','5',0, '5','0','6',0, '5','0','7',0, '5','0','8',0, '5','0','9',0,
    '5','1','0',0, '5','1','1',0, '5','1','2',0, '5','1','3',0, '5','1','4',0,
    '5','1','5',0, '5','1','6',0, '5','1','7',0, '5','1','8',0, '5','1','9',0,
    '5','2','0',0, '5','2','1',0, '5','2','2',0, '5','2','3',0, '5','2','4',0,
    '5','2','5',0, '5','2','6',0, '5','2','7',0, '5','2','8',0, '5','2','9',0,
    '5','3','0',0, '5','3','1',0, '5','3','2',0, '5','3','3',0, '5','3','4',0,
    '5','3','5',0, '5','3','6',0, '5','3','7',0, '5','3','8',0, '5','3','9',0,
    '5','4','0',0, '5','4','1',0, '5','4','2',0, '5','4','3',0, '5','4','4',0,
    '5','4','5',0, '5','4','6',0, '5','4','7',0, '5','4','8',0, '5','4','9',0,
    '5','5','0',0, '5','5','1',0, '5','5','2',0, '5','5','3',0, '5','5','4',0,
    '5','5','5',0, '5','5','6',0, '5','5','7',0, '5','5','8',0, '5','5','9',0,
    '5','6','0',0, '5','6','1',0, '5','6','2',0, '5','6','3',0, '5','6','4',0,
    '5','6','5',0, '5','6','6',0, '5','6','7',0, '5','6','8',0, '5','6','9',0,
    '5','7','0',0, '5','7','1',0, '5','7','2',0, '5','7','3',0, '5','7','4',0,
    '5','7','5',0, '5','7','6',0, '5','7','7',0, '5','7','8',0, '5','7','9',0,
    '5','8','0',0, '5','8','1',0, '5','8','2',0, '5','8','3',0, '5','8','4',0,
    '5','8','5',0, '5','8','6',0, '5','8','7',0, '5','8','8',0, '5','8','9',0,
    '5','9','0',0, '5','9','1',0, '5','9','2',0, '5','9','3',0, '5','9','4',0,
    '5','9','5',0, '5','9','6',0, '5','9','7',0, '5','9','8',0, '5','9','9',0,
    '6','0','0',0, '6','0','1',0, '6','0','2',0, '6','0','3',0, '6','0','4',0,
    '6','0','5',0, '6','0','6',0, '6','0','7',0, '6','0','8',0, '6','0','9',0,
    '6','1','0',0, '6','1','1',0, '6','1','2',0, '6','1','3',0, '6','1','4',0,
    '6','1','5',0, '6','1','6',0, '6','1','7',0, '6','1','8',0, '6','1','9',0,
    '6','2','0',0, '6','2','1',0, '6','2','2',0, '6','2','3',0, '6','2','4',0,
    '6','2','5',0, '6','2','6',0, '6','2','7',0, '6','2','8',0, '6','2','9',0,
    '6','3','0',0, '6','3','1',0, '6','3','2',0, '6','3','3',0, '6','3','4',0,
    '6','3','5',0, '6','3','6',0, '6','3','7',0, '6','3','8',0, '6','3','9',0,
    '6','4','0',0, '6','4','1',0, '6','4','2',0, '6','4','3',0, '6','4','4',0,
    '6','4','5',0, '6','4','6',0, '6','4','7',0, '6','4','8',0, '6','4','9',0,
    '6','5','0',0, '6','5','1',0, '6','5','2',0, '6','5','3',0, '6','5','4',0,
    '6','5','5',0, '6','5','6',0, '6','5','7',0, '6','5','8',0, '6','5','9',0,
    '6','6','0',0, '6','6','1',0, '6','6','2',0, '6','6','3',0, '6','6','4',0,
    '6','6','5',0, '6','6','6',0, '6','6','7',0, '6','6','8',0, '6','6','9',0,
    '6','7','0',0, '6','7','1',0, '6','7','2',0, '6','7','3',0, '6','7','4',0,
    '6','7','5',0, '6','7','6',0, '6','7','7',0, '6','7','8',0, '6','7','9',0,
    '6','8','0',0, '6','8','1',0, '6','8','2',0, '6','8','3',0, '6','8','4',0,
    '6','8','5',0, '6','8','6',0, '6','8','7',0, '6','8','8',0, '6','8','9',0,
    '6','9','0',0, '6','9','1',0, '6','9','2',0, '6','9','3',0, '6','9','4',0,
    '6','9','5',0, '6','9','6',0, '6','9','7',0, '6','9','8',0, '6','9','9',0,
    '7','0','0',0, '7','0','1',0, '7','0','2',0, '7','0','3',0, '7','0','4',0,
    '7','0','5',0, '7','0','6',0, '7','0','7',0, '7','0','8',0, '7','0','9',0,
    '7','1','0',0, '7','1','1',0, '7','1','2',0, '7','1','3',0, '7','1','4',0,
    '7','1','5',0, '7','1','6',0, '7','1','7',0, '7','1','8',0, '7','1','9',0,
    '7','2','0',0, '7','2','1',0, '7','2','2',0, '7','2','3',0, '7','2','4',0,
    '7','2','5',0, '7','2','6',0, '7','2','7',0, '7','2','8',0, '7','2','9',0,
    '7','3','0',0, '7','3','1',0, '7','3','2',0, '7','3','3',0, '7','3','4',0,
    '7','3','5',0, '7','3','6',0, '7','3','7',0, '7','3','8',0, '7','3','9',0,
    '7','4','0',0, '7','4','1',0, '7','4','2',0, '7','4','3',0, '7','4','4',0,
    '7','4','5',0, '7','4','6',0, '7','4','7',0, '7','4','8',0, '7','4','9',0,
    '7','5','0',0, '7','5','1',0, '7','5','2',0, '7','5','3',0, '7','5','4',0,
    '7','5','5',0, '7','5','6',0, '7','5','7',0, '7','5','8',0, '7','5','9',0,
    '7','6','0',0, '7','6','1',0, '7','6','2',0, '7','6','3',0, '7','6','4',0,
    '7','6','5',0, '7','6','6',0, '7','6','7',0, '7','6','8',0, '7','6','9',0,
    '7','7','0',0, '7','7','1',0, '7','7','2',0, '7','7','3',0, '7','7','4',0,
    '7','7','5',0, '7','7','6',0, '7','7','7',0, '7','7','8',0, '7','7','9',0,
    '7','8','0',0, '7','8','1',0, '7','8','2',0, '7','8','3',0, '7','8','4',0,
    '7','8','5',0, '7','8','6',0, '7','8','7',0, '7','8','8',0, '7','8','9',0,
    '7','9','0',0, '7','9','1',0, '7','9','2',0, '7','9','3',0, '7','9','4',0,
    '7','9','5',0, '7','9','6',0, '7','9','7',0, '7','9','8',0, '7','9','9',0,
    '8','0','0',0, '8','0','1',0, '8','0','2',0, '8','0','3',0, '8','0','4',0,
    '8','0','5',0, '8','0','6',0, '8','0','7',0, '8','0','8',0, '8','0','9',0,
    '8','1','0',0, '8','1','1',0, '8','1','2',0, '8','1','3',0, '8','1','4',0,
    '8','1','5',0, '8','1','6',0, '8','1','7',0, '8','1','8',0, '8','1','9',0,
    '8','2','0',0, '8','2','1',0, '8','2','2',0, '8','2','3',0, '8','2','4',0,
    '8','2','5',0, '8','2','6',0, '8','2','7',0, '8','2','8',0, '8','2','9',0,
    '8','3','0',0, '8','3','1',0, '8','3','2',0, '8','3','3',0, '8','3','4',0,
    '8','3','5',0, '8','3','6',0, '8','3','7',0, '8','3','8',0, '8','3','9',0,
    '8','4','0',0, '8','4','1',0, '8','4','2',0, '8','4','3',0, '8','4','4',0,
    '8','4','5',0, '8','4','6',0, '8','4','7',0, '8','4','8',0, '8','4','9',0,
    '8','5','0',0, '8','5','1',0, '8','5','2',0, '8','5','3',0, '8','5','4',0,
    '8','5','5',0, '8','5','6',0, '8','5','7',0, '8','5','8',0, '8','5','9',0,
    '8','6','0',0, '8','6','1',0, '8','6','2',0, '8','6','3',0, '8','6','4',0,
    '8','6','5',0, '8','6','6',0, '8','6','7',0, '8','6','8',0, '8','6','9',0,
    '8','7','0',0, '8','7','1',0, '8','7','2',0, '8','7','3',0, '8','7','4',0,
    '8','7','5',0, '8','7','6',0, '8','7','7',0, '8','7','8',0, '8','7','9',0,
    '8','8','0',0, '8','8','1',0, '8','8','2',0, '8','8','3',0, '8','8','4',0,
    '8','8','5',0, '8','8','6',0, '8','8','7',0, '8','8','8',0, '8','8','9',0,
    '8','9','0',0, '8','9','1',0, '8','9','2',0, '8','9','3',0, '8','9','4',0,
    '8','9','5',0, '8','9','6',0, '8','9','7',0, '8','9','8',0, '8','9','9',0,
    '9','0','0',0, '9','0','1',0, '9','0','2',0, '9','0','3',0, '9','0','4',0,
    '9','0','5',0, '9','0','6',0, '9','0','7',0, '9','0','8',0, '9','0','9',0,
    '9','1','0',0, '9','1','1',0, '9','1','2',0, '9','1','3',0, '9','1','4',0,
    '9','1','5',0, '9','1','6',0, '9','1','7',0, '9','1','8',0, '9','1','9',0,
    '9','2','0',0, '9','2','1',0, '9','2','2',0, '9','2','3',0, '9','2','4',0,
    '9','2','5',0, '9','2','6',0, '9','2','7',0, '9','2','8',0, '9','2','9',0,
    '9','3','0',0, '9','3','1',0, '9','3','2',0, '9','3','3',0, '9','3','4',0,
    '9','3','5',0, '9','3','6',0, '9','3','7',0, '9','3','8',0, '9','3','9',0,
    '9','4','0',0, '9','4','1',0, '9','4','2',0, '9','4','3',0, '9','4','4',0,
    '9','4','5',0, '9','4','6',0, '9','4','7',0, '9','4','8',0, '9','4','9',0,
    '9','5','0',0, '9','5','1',0, '9','5','2',0, '9','5','3',0, '9','5','4',0,
    '9','5','5',0, '9','5','6',0, '9','5','7',0, '9','5','8',0, '9','5','9',0,
    '9','6','0',0, '9','6','1',0, '9','6','2',0, '9','6','3',0, '9','6','4',0,
    '9','6','5',0, '9','6','6',0, '9','6','7',0, '9','6','8',0, '9','6','9',0,
    '9','7','0',0, '9','7','1',0, '9','7','2',0, '9','7','3',0, '9','7','4',0,
    '9','7','5',0, '9','7','6',0, '9','7','7',0, '9','7','8',0, '9','7','9',0,
    '9','8','0',0, '9','8','1',0, '9','8','2',0, '9','8','3',0, '9','8','4',0,
    '9','8','5',0, '9','8','6',0, '9','8','7',0, '9','8','8',0, '9','8','9',0,
    '9','9','0',0, '9','9','1',0, '9','9','2',0, '9','9','3',0, '9','9','4',0,
    '9','9','5',0, '9','9','6',0, '9','9','7',0, '9','9','8',0, '9','9','9',0 };

/* *INDENT-ON* */

/* "inline" */
#define prepbuf(buffer, num, tail)                      \
{                                                       \
  char *s = buffer + 4;                 \
  const char *ap = atoi_tab + (num << 2);       \
                                                        \
  strcpy(buffer, ":%s 000 %s ");                        \
  *s++ = *ap++;                                         \
  *s++ = *ap++;                                         \
  *s = *ap;                                             \
  strcpy(s + 5, tail);                                  \
}

char* err_str(int n)
{
  Numeric* p;

  assert(0 < n);
  assert(n < ERR_LASTERROR);
  assert(0 != replyTable[n].value);

  p = &replyTable[n];
  prepbuf(numbuff, p->value, p->format);

  return numbuff;
}

char* rpl_str(int n)
{
  Numeric* p;

  assert(0 < n);
  assert(n < ERR_LASTERROR);
  assert(0 != replyTable[n].value);

  p = &replyTable[n];
  prepbuf(numbuff, p->value, p->format);

  return numbuff;
}

