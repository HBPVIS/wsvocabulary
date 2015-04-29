#include <wsvoc/wsvoc.h>
#include <zeq/zeq.h>
#include <boost/bind.hpp>
#include <lunchbox/uri.h>

zeq::Publisher* publisher;
zeq::Subscriber* subscriber;

using namespace wsvoc;

void ReceiveCallback( const zeq::Event& event )
{
  wsvoc::data::Vector3d result = deserializeVector3d(event);

  std::cout << "Received " << result.x << " "
                           << result.y << " "
                           << result.z << std::endl;

  std::sort(&result.x, (&result.z) + 1 );
//  std::swap(result.x, result.z);

  zeq::Event response = serializeVector3d(result);

  std::cout << "Sending... " << result.x << " "
                             << result.y << " "
                             << result.z << std::endl;


  publisher->publish(response);

}


int main(int /*argc*/, char** argv)
{



  publisher = new zeq::Publisher( lunchbox::URI(argv[1] ) );

  subscriber = new zeq::Subscriber( lunchbox::URI(argv[2] ));


  subscriber->registerHandler( wsvoc::EVENT_VECTOR3D,
                              boost::bind( &ReceiveCallback, _1));

  while(true)
  {

    while( subscriber->receive( 200 )){}

	}

  return 0;
}
