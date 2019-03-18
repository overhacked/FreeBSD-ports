# Created by: Ross Williams <ross@ross-williams.net>
# $FreeBSD$

PORTNAME=	libzbxmodbus
PORTVERSION=	0.9
PORTREVISION=	3
CATEGORIES=	net-mgmt

FLAVORS=        zabbix40 zabbix30 zabbix32 zabbix34
FLAVOR?=	${FLAVORS:[1]}
PKGNAMEPREFIX=	${FLAVOR}-

MASTER_SITES=   https://github.com/${GH_ACCOUNT}/${PORTNAME}/releases/download/v${DISTVERSION}/

MAINTAINER=	ross@ross-williams.net
COMMENT=	Zabbix server module for collecting metric from MODBUS (TCP & serial) hosts

LICENSE=	GPLv2+

BUILD_DEPENDS=	${NONEXISTENT}:net-mgmt/${PKGNAMEPREFIX}server:patch
RUN_DEPENDS=	zabbix_server:net-mgmt/${PKGNAMEPREFIX}server

CONFLICTS=	zabbix[0-24-9][0-13-9]-libzbxmodbus zabbix[0-9]-libzbxmodbus

USES=		gmake libtool pkgconfig

GH_ACCOUNT=	v-zhuravlev

GNU_CONFIGURE=	yes
GET_ZBX_WRKSRC=	cd ${.CURDIR:H:H}/net-mgmt/${PKGNAMEPREFIX}server && make -V WRKSRC
# --with-zabbix=$$(${GET_ZBX_WRKSRC})
.if ${FLAVOR:U} == zabbix30
CONFIGURE_ARGS= --enable-zabbix-3
.else # zabbix >= 3.2
CONFIGURE_ARGS=	--enable-zabbix-3.2
.endif

USE_LDCONFIG=	yes

PORTSCOUT=	skipv:latest,gh-pages

.include <bsd.port.mk>
