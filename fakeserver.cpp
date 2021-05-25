#include "fakeserver.h"
#include <QDebug>
#include <QThread>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>
#include <grpc++/security/server_credentials.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerWriter;
using grpc::Status;

class GRpcThread : public QThread
{
public:
	GRpcThread(int port, FakeServer *server)
	{
		ep = QString("0.0.0.0:%1").arg(port);
		service = server;
		qDebug()<< " ** Initializing **";
	}

	void run()
	{
		std::string ep(this->ep.toStdString());
		ServerBuilder builder;
		builder.AddListeningPort(ep, grpc::InsecureServerCredentials());
		builder.RegisterService(service);
		std::unique_ptr<Server> server(builder.BuildAndStart());
		server->Wait();
	}
	QString ep;
	FakeServer *service;
};

int FakeServer::start()
{
	GRpcThread *thr = new GRpcThread(40041, this);
	thr->start();
	return 0;
}

grpc::Status FakeServer::GetRecordDetails(grpc::ServerContext *context, const vms::CameraQ *request, vms::RecordDetails *response)
{
	qDebug()<< "runnnniiiinnngggggggg";
	response->set_record_begin_time(10);
	response->set_record_end_time(22);
	for (int var = 1; var < 5; ++var) {
		auto dList = response->add_detail();
		dList->set_begin_time(100*var);
		dList->set_end_time(2000*var);
	}
	return grpc::Status::OK;
}
