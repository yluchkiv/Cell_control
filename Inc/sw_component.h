#ifndef SW_COMPONENT_H_
#define SW_COMPONENT_H_

enum class processing_t { message, gate };

processing_t process_request(int a, int b);

#endif /* SW_COMPONENT_H_ */
