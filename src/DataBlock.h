#pragma once

/*!
* \file DataBlock.h
* \brief Defines class DataBlock to store the necessary data for trainer and param_loader
* \author
*	- v-fetia
*/
#include "Util.h"
#include <multiverso.h>
#include "HuffmanEncoder.h"

/*!
* \brief The class DataBlock stores train for trainer and param_loader
*/
class DataBlock : public multiverso::DataBlockBase
{
public:
	/*!
	* \brief Get the number of sentences stored in DataBlock
	* \return the number of sentences
	*/
	size_t Size();
	/*!
	* \brief Add a new sentence to the DataBlock
	* \param sentence the starting address of the sentence
	* \param sentence_length the length of the sentence
	* \param word_count the number of words when getting the sentence from train-file
	* \param next_random the seed for getting random number
	*/
	void Add(int *sentence, int sentence_length, int64_t word_count, uint64_t next_random);
	/*!
	* \brief Get the information of the index-th sentence
	* \param index the id of the sentence
	* \param sentence the starting address of the sentence
	* \param sentence_length the number of words in the sentence
	* \param word_count the number of words when getting the sentence from train-file
	* \param next_random the seed for getting random number
	*/
	void Get(int index, int* &sentence, int &sentence_length, int64_t &word_count, uint64_t &next_random);


	void UpdateNextRandom();

	void AddTable(int table_id);

	std::vector <int> & GetTables();

	void ReleaseSentences();

	int GetEpochId();

	void SetEpochId(const int epoch_id);

private:
	struct Sentence
	{
		int* head;
		int length;
		int64_t word_count;
		uint64_t next_random;
		Sentence(int *head, int length, int64_t word_count, uint64_t next_random)
			:head(head), length(length), word_count(word_count), next_random(next_random){}
		void Get(int* &local_head, int &sentence_length, int64_t &local_word_count, uint64_t &local_next_random)
		{
			local_head = head;
			sentence_length = length;
			local_word_count = word_count;
			local_next_random = next_random;
		}
	};

	std::vector <int> m_tables;
	std::vector <Sentence> m_sentences;
	int m_epoch_id;
};