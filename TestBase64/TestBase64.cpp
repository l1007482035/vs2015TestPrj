// TestBase64.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestBase64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;


#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h> // 包含 BUF_MEM 定义
#include <openssl/err.h>    // 包含错误处理函数
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int base64_encode(const unsigned char *input, long length, char **output)
{
	BIO *bio, *b64;
	BUF_MEM *bufferPtr;

	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);

	// 设置 BIO 不要对 Base64 编码添加换行符
	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

	BIO_write(bio, input, length);
	BIO_flush(bio);
	BIO_get_mem_ptr(bio, &bufferPtr);
	BIO_set_close(bio, BIO_NOCLOSE);
	BIO_free_all(bio);

	// 分配足够的空间用于输出以及空终止符
	*output = new char[bufferPtr->length + 1];
	if (*output == NULL) return 0;
	memcpy(*output, bufferPtr->data, bufferPtr->length);
	(*output)[bufferPtr->length] = '\0'; // 空终止字符串

	return 1;
}

int base64_decode(const char *input, unsigned char **output, size_t *output_len)
{
	BIO *bio, *b64;

	// 创建一个内存 BIO 来读取输入数据
	bio = BIO_new_mem_buf(input, -1); // 使用 -1 让 OpenSSL 自动确定长度
	if (!bio) {
		return 0;
	}

	// 创建 Base64 过滤器并推入堆栈
	b64 = BIO_new(BIO_f_base64());
	if (!b64) {
		BIO_free_all(bio);
		return 0;
	}
	bio = BIO_push(b64, bio);

	// 设置 BIO 不要期望输入中的换行符
	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

	// 动态分配一个足够大的缓冲区来存储解码后的数据
	unsigned char *decoded_data = NULL;
	size_t decoded_length = 0;
	decoded_data = new unsigned char[strlen(input) / 4 * 3 + 1];
	if (!decoded_data) {
		BIO_free_all(bio);
		return 0;
	}

	// 执行解码操作
	decoded_length = BIO_read(bio, decoded_data, strlen(input) / 4 * 3);
	if (decoded_length <= 0) {
		free(decoded_data);
		BIO_free_all(bio);
		return 0; // 解码失败
	}

	// 将解码后的数据复制到输出指针，并更新输出长度
	*output = decoded_data;
	*output_len = decoded_length;

	BIO_free_all(bio);

	return 1;
}

int main()
{
	const char *original_data = "123456";
	char *encoded_data = NULL;
	unsigned char *decoded_data = NULL;
	size_t decoded_length = 0;

	// Encoding data
	if (!base64_encode((const unsigned char *)original_data, strlen(original_data), &encoded_data)) {
		fprintf(stderr, "Failed to encode\n");
		return -1;
	}
	printf("Encoded: %s\n", encoded_data);

	// Decoding data
	if (!base64_decode(encoded_data, &decoded_data, &decoded_length)) {
		fprintf(stderr, "Failed to decode\n");
		free(encoded_data);
		return -1;
	}
	printf("Decoded: %.*s\n", (int)decoded_length, decoded_data);

	free(encoded_data);
	free(decoded_data);

	return 0;
}