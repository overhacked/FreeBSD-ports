# Created by: Ross Williams <ross@ross-williams.net>
# $FreeBSD$

PORTNAME=	libzbxmodbus
PORTVERSION=	0.9
PORTREVISION=	1
CATEGORIES=	net-mgmt
PKGNAMEPREFIX=	zabbix34-

MASTER_SITES=   https://github.com/${GH_ACCOUNT}/${PORTNAME}/releases/download/v${DISTVERSION}/

MAINTAINER=	ross@ross-williams.net
COMMENT=	Zabbix server module for collecting metric from MODBUS (TCP & serial) hosts

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${NONEXISTENT}:net-mgmt/${PKGNAMEPREFIX}server:patch
RUN_DEPENDS=	zabbix_server:net-mgmt/${PKGNAMEPREFIX}server

CONFLICTS=	zabbix[0-24-9][0-13-9]-libzbxmodbus zabbix[0-9]-libzbxmodbus

USES=		gmake libtool pkgconfig

GH_ACCOUNT=	v-zhuravlev

GNU_CONFIGURE=	yes
GET_ZBX_WRKSRC=	cd ${.CURDIR:H:H}/net-mgmt/${PKGNAMEPREFIX}server && make -V WRKSRC
CONFIGURE_ARGS=	--enable-zabbix-3.2
# --with-zabbix=$$(${GET_ZBX_WRKSRC})

USE_LDCONFIG=	yes

PORTSCOUT=	skipv:latest,gh-pages

do-install:
		${INSTALL_LIB} ${WRKSRC}/src/.libs/libzbxmodbus.so ${STAGEDIR}${PREFIX}/lib/libzbxmodbus.so

.include <bsd.port.mk>
