#ifndef OPENMITTSU_DATABASE_INTERNAL_DATABASEUSERMESSAGE_H_
#define OPENMITTSU_DATABASE_INTERNAL_DATABASEUSERMESSAGE_H_

#include <QString>
#include <QSqlQuery>

#include "src/protocol/MessageId.h"
#include "src/protocol/MessageTime.h"
#include "src/database/internal/DatabaseMessage.h"
#include "src/dataproviders/messages/UserMessage.h"

namespace openmittsu {
	namespace database {
		namespace internal {

			class DatabaseUserMessage : public virtual DatabaseMessage, public virtual openmittsu::dataproviders::messages::UserMessage {
			public:
				explicit DatabaseUserMessage(InternalDatabaseInterface* database, openmittsu::protocol::MessageId const& messageId);
				virtual ~DatabaseUserMessage();

				virtual bool isRead() const override;

				/** Encodes whether all data is available, i.e. referenced image or video data is available. */
				virtual bool isSaved() const override;

				virtual openmittsu::dataproviders::messages::UserMessageState getMessageState() const override;
				virtual void setMessageState(openmittsu::dataproviders::messages::UserMessageState const& messageState, openmittsu::protocol::MessageTime const& when) override;

				virtual void setIsSent() override;
				virtual openmittsu::protocol::MessageTime getReceivedAt() const override;
				virtual openmittsu::protocol::MessageTime getSeenAt() const override;
				virtual bool isStatusMessage() const override;

				virtual QString getCaption() const override;
			};

		}
	}
}

#endif // OPENMITTSU_DATABASE_INTERNAL_DATABASEUSERMESSAGE_H_
