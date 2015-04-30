/* Copyright (c) 2014-2015, Human Brain Project Workshop
 */

#include <wsvoc/wsvoc.h>
#include <zeq/zeq.h>
#include <boost/bind.hpp>
#include <lunchbox/uri.h>

zeq::Publisher* publisher;
//zeq::Subscriber* subscriber;

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


  /**
   * Init publisher with URI taken from command line argument as follows:
   *  - WITH ZeroConf: schema://
   *  - WITHOUT ZeroConf: schema://ip:port
   *
   *  Note: Publisher URI must use its machine IP address.
   *
   * */
  publisher = new zeq::Publisher( lunchbox::URI(argv[1] ) );

  /**
   *  When using static publisher/subscriber it's necessary to create URI
   *  as an object, avoiding to do it on the same line as follows:
   *  subscriber(lunchbox::URI(uri))
   *
   */
  lunchbox::URI uri (argv[2]);
  zeq::Subscriber subscriber ( uri );


  /**
   * Init subscriber with URI taken from command line argument as follows:
   *  - WITH ZeroConf: schema://
   *  - WITHOUT ZeroConf: schema://ip:port
   *
   *  Note: Subscriber URI must use publisher's machine IP address.
   *
   * */
  subscriber.registerHandler( wsvoc::EVENT_VECTOR3D,
                              boost::bind( &ReceiveCallback, _1));

  while(true)
  {

    while( subscriber.receive( 200 )){}

	}

  return 0;
}
