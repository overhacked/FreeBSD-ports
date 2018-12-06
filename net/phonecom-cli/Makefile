# Created by: Ross Williams <ross@ross-williams.net>
# $FreeBSD$

PORTNAME=	phonecom-cli
PORTVERSION=	1.0.7
DISTVERSIONPREFIX=	v
CATEGORIES=	net

MAINTAINER=	ross@ross-williams.net
COMMENT=	Phone.com API CLI tool

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		go
GO_PKGNAME=	phonecom
PLIST_FILES= bin/${GO_PKGNAME}

USE_GITHUB=	yes
GH_ACCOUNT=phonedotcom
GH_PROJECT=API-Swagger
GH_TUPLE=	golang:net:c394268:golangnet/phonecom-cli/src/golang.org/x/net \
			go-resty:resty:v0.13:goresty/phonecom-cli/src/gopkg.in/go-resty/resty.v0 \
			urfave:cli:b67dcf9:urfave/phonecom-cli/src/github.com/urfave/cli \
			yukithm:json2csv:e86d456:yukithm/phonecom-cli/src/github.com/yukithm/json2csv \
			stretchr:testify:8019298:stretchr/phonecom-cli/src/github.com/stretchr/testify \
			phonedotcom:API-SDK-go:feace2f:phonedotcomsdk/phonecom-cli/src/github.com/phonedotcom/API-SDK-go

.include <bsd.port.pre.mk>

post-extract:
	${LN} -sf ${WRKSRC}/phonecom-cli/src ${WRKDIR}

.include <bsd.port.post.mk>
