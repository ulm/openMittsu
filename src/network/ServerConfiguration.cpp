#include "src/network/ServerConfiguration.h"

#include "src/exceptions/IllegalArgumentException.h"

#include <string>
#include <cstring>
#include <algorithm>

#include <QString>
#include <QFile>
#include <QSettings>

namespace openmittsu {
	namespace network {

ServerConfiguration::ServerConfiguration() : 
	serverHost(QStringLiteral("g-xx.0.threema.ch")), 
	serverPort(5222), 
	serverLongTermPublicKey(openmittsu::crypto::PublicKey::fromHexString(QStringLiteral("b851ae1bf275ebe6851ca7f5206b495080927159787e9aaabbeb4e55af09d805"))), 
	apiServerHost(QStringLiteral("https://api.threema.ch")),
	apiServerAgent(QStringLiteral("Threema/openMittsu")),
	apiServerCertificate(QStringLiteral("LS0tLS1CRUdJTiBDRVJUSUZJQ0FURS0tLS0tCk1JSUVZVENDQTBtZ0F3SUJBZ0lKQU0xRFIvREJSRnBRTUEwR0NTcUdTSWIzRFFFQkJRVUFNSDB4Q3pBSkJnTlYKQkFZVEFrTklNUXN3Q1FZRFZRUUlFd0phU0RFUE1BMEdBMVVFQnhNR1duVnlhV05vTVJBd0RnWURWUVFLRXdkVQphSEpsWlcxaE1Rc3dDUVlEVlFRTEV3SkRRVEVUTUJFR0ExVUVBeE1LVkdoeVpXVnRZU0JEUVRFY01Cb0dDU3FHClNJYjNEUUVKQVJZTlkyRkFkR2h5WldWdFlTNWphREFlRncweE1qRXhNVE14TVRVNE5UaGFGdzB6TWpFeE1EZ3gKTVRVNE5UaGFNSDB4Q3pBSkJnTlZCQVlUQWtOSU1Rc3dDUVlEVlFRSUV3SmFTREVQTUEwR0ExVUVCeE1HV25WeQphV05vTVJBd0RnWURWUVFLRXdkVWFISmxaVzFoTVFzd0NRWURWUVFMRXdKRFFURVRNQkVHQTFVRUF4TUtWR2h5ClpXVnRZU0JEUVRFY01Cb0dDU3FHU0liM0RRRUpBUllOWTJGQWRHaHlaV1Z0WVM1amFEQ0NBU0l3RFFZSktvWkkKaHZjTkFRRUJCUUFEZ2dFUEFEQ0NBUW9DZ2dFQkFLOEdkb1Q3SXBOQzNEejdJVUdZVzlwT0J3eCs5RW5EWnJrTgpWRDhsM0tmQkhqR1RkaTlnUTZOaCttUTkveVE4MjU0VDJiaWc5cDBoY244a2pnRVFnSldIcE5oWW5PaHkzaTBqCmNtbHpiMU1GL2RlRmpKVnR1TVAzdHFUd2lNYXZwd2VvYTIwbEdEbi9DTFpvZHUwUmE4b0w3OGI2RlZ6dE5rV2cKUGRpV0NsTWswSlBQTWxmTEVpSzhoZkhFKzZtUlZYbWkxMml0SzFzZW1td3lIS2RqOWZHNFg5K3JRMnNLdUxmZQpqeDd1RnhuQUYrR2l2Q3VDbzh4Zk9lc0x3NzJ2eCtXN21tZFlzaGcvbFhPY3F2c3pRUS9MbUZFVlFZeE5hZWVWCm5QU0FzK2h0OHZVUFc0c1g5SWtYS1ZnQkpkMVIxaXNVcG9GNmRLbFVleG12THhFeWY1Y0NBd0VBQWFPQjR6Q0IKNERBZEJnTlZIUTRFRmdRVXc2TGFDNytKNjJyS2RhVEEzN2tBWVlVYnJrZ3dnYkFHQTFVZEl3U0JxRENCcFlBVQp3NkxhQzcrSjYycktkYVRBMzdrQVlZVWJya2loZ1lHa2Z6QjlNUXN3Q1FZRFZRUUdFd0pEU0RFTE1Ba0dBMVVFCkNCTUNXa2d4RHpBTkJnTlZCQWNUQmxwMWNtbGphREVRTUE0R0ExVUVDaE1IVkdoeVpXVnRZVEVMTUFrR0ExVUUKQ3hNQ1EwRXhFekFSQmdOVkJBTVRDbFJvY21WbGJXRWdRMEV4SERBYUJna3Foa2lHOXcwQkNRRVdEV05oUUhSbwpjbVZsYldFdVkyaUNDUUROUTBmd3dVUmFVREFNQmdOVkhSTUVCVEFEQVFIL01BMEdDU3FHU0liM0RRRUJCUVVBCkE0SUJBUUFSSE15SUhCREZ1bCtodmpBQ3Q2cjBFQUhZd1I5R1FTZ2hJUXNmSHQ4Y3lWY3ptRW5KSDlocnZoOVEKVml2bTdtcmZ2ZWlobU5YQW40V2xHd1ErQUN1VnRUTHh3OEVyYlNUN0lNQU94OW5wSGYva25nblo0blN3VVJGOQpyQ0V5SHExNzlwTlhwT3paMjU3RTVyMGF2TU5OWFhEd3VsdzAzaUJFMjFlYmQwMHBHMTFHVnEvSTI2cys4QmpuCkRLUlBxdUtyU080L2x1RUR2TDRuZ2lRalpwMzJTOVoxSzlzVk96cXRRN0k5enplVUFEbTNhVmEvQnBhdzRpTVIKMVNJN285YUpZaVJpMWd4WVAyQlVBMUlGcXI4Tnp5ZkdEN3RSSGRxN2JaT3hYQWx1djgxZGNiejBTQlg4U2dWMQo0SEVLYzZ4TUFObllzL2FZS2p2bVAwVnBPdlJVCi0tLS0tRU5EIENFUlRJRklDQVRFLS0tLS0=")),
	blobServerRequestDownloadUrl(QStringLiteral("https://%1.blob.threema.ch/%2")),
	blobServerRequestDownloadFinishedUrl(QStringLiteral("https://%1.blob.threema.ch/%2/done")),
	blobServerRequestUploadUrl(QStringLiteral("https://upload.blob.threema.ch/upload")),
	blobServerRequestAgent(QStringLiteral("Threema/openMittsu")),
	blobServerCertificate(QStringLiteral("LS0tLS1CRUdJTiBDRVJUSUZJQ0FURS0tLS0tCk1JSUVZVENDQTBtZ0F3SUJBZ0lKQU0xRFIvREJSRnBRTUEwR0NTcUdTSWIzRFFFQkJRVUFNSDB4Q3pBSkJnTlYKQkFZVEFrTklNUXN3Q1FZRFZRUUlFd0phU0RFUE1BMEdBMVVFQnhNR1duVnlhV05vTVJBd0RnWURWUVFLRXdkVQphSEpsWlcxaE1Rc3dDUVlEVlFRTEV3SkRRVEVUTUJFR0ExVUVBeE1LVkdoeVpXVnRZU0JEUVRFY01Cb0dDU3FHClNJYjNEUUVKQVJZTlkyRkFkR2h5WldWdFlTNWphREFlRncweE1qRXhNVE14TVRVNE5UaGFGdzB6TWpFeE1EZ3gKTVRVNE5UaGFNSDB4Q3pBSkJnTlZCQVlUQWtOSU1Rc3dDUVlEVlFRSUV3SmFTREVQTUEwR0ExVUVCeE1HV25WeQphV05vTVJBd0RnWURWUVFLRXdkVWFISmxaVzFoTVFzd0NRWURWUVFMRXdKRFFURVRNQkVHQTFVRUF4TUtWR2h5ClpXVnRZU0JEUVRFY01Cb0dDU3FHU0liM0RRRUpBUllOWTJGQWRHaHlaV1Z0WVM1amFEQ0NBU0l3RFFZSktvWkkKaHZjTkFRRUJCUUFEZ2dFUEFEQ0NBUW9DZ2dFQkFLOEdkb1Q3SXBOQzNEejdJVUdZVzlwT0J3eCs5RW5EWnJrTgpWRDhsM0tmQkhqR1RkaTlnUTZOaCttUTkveVE4MjU0VDJiaWc5cDBoY244a2pnRVFnSldIcE5oWW5PaHkzaTBqCmNtbHpiMU1GL2RlRmpKVnR1TVAzdHFUd2lNYXZwd2VvYTIwbEdEbi9DTFpvZHUwUmE4b0w3OGI2RlZ6dE5rV2cKUGRpV0NsTWswSlBQTWxmTEVpSzhoZkhFKzZtUlZYbWkxMml0SzFzZW1td3lIS2RqOWZHNFg5K3JRMnNLdUxmZQpqeDd1RnhuQUYrR2l2Q3VDbzh4Zk9lc0x3NzJ2eCtXN21tZFlzaGcvbFhPY3F2c3pRUS9MbUZFVlFZeE5hZWVWCm5QU0FzK2h0OHZVUFc0c1g5SWtYS1ZnQkpkMVIxaXNVcG9GNmRLbFVleG12THhFeWY1Y0NBd0VBQWFPQjR6Q0IKNERBZEJnTlZIUTRFRmdRVXc2TGFDNytKNjJyS2RhVEEzN2tBWVlVYnJrZ3dnYkFHQTFVZEl3U0JxRENCcFlBVQp3NkxhQzcrSjYycktkYVRBMzdrQVlZVWJya2loZ1lHa2Z6QjlNUXN3Q1FZRFZRUUdFd0pEU0RFTE1Ba0dBMVVFCkNCTUNXa2d4RHpBTkJnTlZCQWNUQmxwMWNtbGphREVRTUE0R0ExVUVDaE1IVkdoeVpXVnRZVEVMTUFrR0ExVUUKQ3hNQ1EwRXhFekFSQmdOVkJBTVRDbFJvY21WbGJXRWdRMEV4SERBYUJna3Foa2lHOXcwQkNRRVdEV05oUUhSbwpjbVZsYldFdVkyaUNDUUROUTBmd3dVUmFVREFNQmdOVkhSTUVCVEFEQVFIL01BMEdDU3FHU0liM0RRRUJCUVVBCkE0SUJBUUFSSE15SUhCREZ1bCtodmpBQ3Q2cjBFQUhZd1I5R1FTZ2hJUXNmSHQ4Y3lWY3ptRW5KSDlocnZoOVEKVml2bTdtcmZ2ZWlobU5YQW40V2xHd1ErQUN1VnRUTHh3OEVyYlNUN0lNQU94OW5wSGYva25nblo0blN3VVJGOQpyQ0V5SHExNzlwTlhwT3paMjU3RTVyMGF2TU5OWFhEd3VsdzAzaUJFMjFlYmQwMHBHMTFHVnEvSTI2cys4QmpuCkRLUlBxdUtyU080L2x1RUR2TDRuZ2lRalpwMzJTOVoxSzlzVk96cXRRN0k5enplVUFEbTNhVmEvQnBhdzRpTVIKMVNJN285YUpZaVJpMWd4WVAyQlVBMUlGcXI4Tnp5ZkdEN3RSSGRxN2JaT3hYQWx1djgxZGNiejBTQlg4U2dWMQo0SEVLYzZ4TUFObllzL2FZS2p2bVAwVnBPdlJVCi0tLS0tRU5EIENFUlRJRklDQVRFLS0tLS0=")) {
	//
}

ServerConfiguration::ServerConfiguration(QString const& serverHost, int serverPort, openmittsu::crypto::PublicKey const& serverLongTermPublicKey, QString const& apiServerHost, QString const& apiServerAgent, QString const& apiServerCertificate, QString const& blobServerRequestDownloadUrl, QString const& blobServerRequestDownloadFinishedUrl, QString const& blobServerRequestUploadUrl, QString const& blobServerRequestAgent, QString const& blobServerCertificate)
	: serverHost(serverHost), serverPort(serverPort), serverLongTermPublicKey(serverLongTermPublicKey), apiServerHost(apiServerHost), apiServerAgent(apiServerAgent), apiServerCertificate(apiServerCertificate), blobServerRequestDownloadUrl(blobServerRequestDownloadUrl), blobServerRequestDownloadFinishedUrl(blobServerRequestDownloadFinishedUrl), blobServerRequestUploadUrl(blobServerRequestUploadUrl), blobServerRequestAgent(blobServerRequestAgent), blobServerCertificate(blobServerCertificate) {
	//
}

QString const& ServerConfiguration::getServerHost() const {
	return serverHost;
}

int ServerConfiguration::getServerPort() const {
	return serverPort;
}

openmittsu::crypto::PublicKey const& ServerConfiguration::getServerLongTermPublicKey() const {
	return serverLongTermPublicKey;
}

QString const& ServerConfiguration::getApiServerHost() const {
	return apiServerHost;
}

QString const& ServerConfiguration::getApiServerAgent() const {
	return apiServerAgent;
}

QString const& ServerConfiguration::getApiServerCertificateAsBase64() const {
	return apiServerCertificate;
}

QString ServerConfiguration::getApiServerFetchPublicKeyForIdUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/%1"));
}

QString ServerConfiguration::getApiServerFetchFeatureLevelsForIdsUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/check_featurelevel"));
}

QString ServerConfiguration::getApiServerSetFeatureLevelUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/set_featurelevel"));
}

QString ServerConfiguration::getApiServerCheckStatusForIdsUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/check"));
}

QString ServerConfiguration::getApiServerCheckRevocationKeyUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/check_revocation_key"));
}

QString ServerConfiguration::getApiServerSetRevocationKeyUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/set_revocation_key"));
}

QString ServerConfiguration::getApiServerLinkEmailToIdUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/link_email"));
}

QString ServerConfiguration::getApiServerLinkMobileNumberToIdUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/link_mobileno"));
}

QString ServerConfiguration::getApiServerRequestCallForVerificationIdUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/link_mobileno_call"));
}

QString ServerConfiguration::getApiServerFetchPrivateInformationForIdUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/fetch_priv"));
}

QString ServerConfiguration::getApiServerMatchMobileNumbersAndEmailsToContactsUrl() const {
	return QString(getApiServerHost()).append(QStringLiteral("/identity/match"));
}


QString const& ServerConfiguration::getBlobServerRequestDownloadUrl() const {
	return blobServerRequestDownloadUrl;
}

QString const& ServerConfiguration::getBlobServerRequestDownloadFinishedUrl() const {
	return blobServerRequestDownloadFinishedUrl;
}

QString const& ServerConfiguration::getBlobServerRequestUploadUrl() const {
	return blobServerRequestUploadUrl;
}

QString const& ServerConfiguration::getBlobServerRequestAgent() const {
	return blobServerRequestAgent;
}

QString const& ServerConfiguration::getBlobServerCertificateAsBase64() const {
	return blobServerCertificate;
}

QString ServerConfiguration::toString() const {
	QString result = QStringLiteral("ServerConfiguration(serverHost = %1, serverPort = %2, serverLongTermPublicKey = %3, apiServerHost = %4, apiServerAgent = %5, apiServerCertificate = %6, imageRequestDownloadUrl = %7, imageRequestDownloadFinishedUrl = %8, imageRequestUploadUrl = %9, imageRequestAgent = %10, imageServerCertificate = %11)")
		.arg(this->getServerHost())
		.arg(QString::number(this->getServerPort()))
		.arg(this->getServerLongTermPublicKey().toQString())
		.arg(this->getApiServerHost())
		.arg(this->getApiServerAgent())
		.arg(this->getApiServerCertificateAsBase64())
		.arg(this->getBlobServerRequestDownloadUrl())
		.arg(this->getBlobServerRequestDownloadFinishedUrl())
		.arg(this->getBlobServerRequestUploadUrl())
		.arg(this->getBlobServerRequestAgent())
		.arg(this->getBlobServerCertificateAsBase64());
	return result;
}


	}
}
