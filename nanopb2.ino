#include "src/test.pb.h"

#include "pb_common.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

void setup() {

  Serial.begin(115200);

  uint8_t buffer[128];
  bool status;
  size_t message_length;

  /* ENCODING */
  {
    TestMessage message = TestMessage_init_zero;
  
    pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  
    message.test_number = 540;
    message.test_number2 = 123;
    message.test_number3 = 456;
  
    status = pb_encode(&ostream, TestMessage_fields, &message);
  
    if (!status)
    {
        Serial.println("Failed to encode");
        return;
    }
  
    message_length = ostream.bytes_written;
  
    Serial.print("Message Length: ");
    Serial.println(message_length);
  
    Serial.print("Message: ");
    for(int i = 0; i<ostream.bytes_written; i++){
      Serial.printf("%02X",buffer[i]);
    }
    Serial.println();
  }

  /* DECODING */
  {
    TestMessage out_message = TestMessage_init_zero;
  
    /* Create a stream that reads from the buffer. */
    pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
    
    /* Now we are ready to decode the message. */
    status = pb_decode(&stream, TestMessage_fields, &out_message);
  
    if (!status)
    {
        printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
    }
  
    Serial.print("Message.test_number: ");
    Serial.println(out_message.test_number);
    Serial.print("Message.test_number2: ");
    Serial.println(out_message.test_number2);
    Serial.print("Message.test_number3: ");
    Serial.println(out_message.test_number3);
  }
}

void loop() {}
