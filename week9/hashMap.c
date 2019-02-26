/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Jonathan Jazdzewski
 * Date: 11/23/18
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}


/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
    for (int b=0;b<hashMapCapacity(map);b++){\
        HashLink * link = map->table[b];
        while(link!=NULL){
            HashLink * next = link->next;
            hashLinkDelete(link);
            link = next;
            map->size -=1;
        }
    }
    free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    int index = HASH_FUNCTION(key) % (hashMapCapacity(map));
    HashLink * link = map->table[index];
    while(link!=NULL){
        char linkKey = *(link->key);
        char keyChar = *(key);
        if (linkKey == keyChar){
            int ret =1;
            for (int b=0;key[b]!='\0' || link->key[b]!='\0';b++){
                    if (key[b]!=link->key[b]){
                        ret = 0;
                    }
                }
                if (ret==1){
                    return &link->value;
                }
        }
        link = link->next;
    }
        return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
    HashLink ** oldTable = map->table;
    HashLink ** newTable = malloc(sizeof(HashLink*) * capacity * 2);
    for (int b=0;b<capacity*2;b++){
        newTable[b] = NULL;
    }
    map->table = newTable;
    map->capacity = capacity *2;
    map->size = 0;
    for (int a=0;a<capacity;a++){
        HashLink * link = oldTable[a];
        while (link!=NULL){
            char * thisKey = malloc(sizeof(char) * (strlen(link->key) + 1));
            strcpy(thisKey,link->key);
            hashMapPut(map,thisKey,link->value);
            HashLink * freeLink = link;
            link = link->next;
            hashLinkDelete(freeLink);
            free(thisKey);
        }
    }
    free(oldTable);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
    int index = HASH_FUNCTION(key) % (hashMapCapacity(map));
    if(hashMapContainsKey(map,key)){
        HashLink * old = map->table[index];
        while (old!=NULL){
            if (*(old->key)==*(key)){
                old->value = value;
            }
            old = old->next;
            map->size += 1;
        }
    } else {
        HashLink * old = map->table[index];
        if (old==NULL){
            map->table[index] = hashLinkNew(key,value,NULL);
            map->size += 1;
            return;
        }
        int count = 1;
        while (old->next!=NULL){
            old = old->next;
            count++;
        }
        if (count>=MAX_TABLE_LOAD-1){
            printf("Resize\n");
            resizeTable(map,hashMapCapacity(map));
            hashMapPut(map,key,value);
        } else {
            HashLink * new = hashLinkNew(key,value,NULL);
            old->next = new;
            map->size = map->size + 1;
        }
    }
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    int index = HASH_FUNCTION(key) % (hashMapCapacity(map));
    HashLink * link = map->table[index];
    char keyVal = *(key);
    while(link!=NULL){
        if (link->next==NULL || *(link->key)==keyVal){
            if (*(link->key)==keyVal){
                map->table[index] = link->next;
                hashLinkDelete(link);
                map->size = map->size -1;
            }
        } else {
            if (*(link->next->key)==keyVal){
                HashLink * oldNext = link->next;
                link->next = link->next->next;
                hashLinkDelete(oldNext);
                map->size = map->size - 1;
            }
        }
        link = link->next;
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    for (int a=0;a<hashMapCapacity(map);a++){
        HashLink * link = map->table[a];
        while (link!=NULL){
            if (*(link->key) == *(key)){
                int ret =1;
                for (int b=0;key[b]!='\0' || link->key[b]!='\0';b++){
                    if (key[b]!=link->key[b]){
                        ret = 0;
                    }
                }
                if (ret==1){
                    return 1;
                }
            }
            link = link->next;
        }
    }
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
    int count = 0;
    for (int a=0; a<map->capacity;a++){
        if (map->table[a]==NULL){
            count ++;
        }
    }
    return count;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    float hashSize = (float)hashMapSize(map);
    float hashCap = (float)hashMapCapacity(map);
    float ratio = hashSize/hashCap;
    return ratio;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
  // FIXME: implement
    for (int a=0;a<hashMapCapacity(map);a++){
        HashLink * link = map->table[a];
        int count = 1;
        printf("Bucket #%d\n",a);
        while (link!=NULL){
            printf("  Link #%d. Value: %d. Key: %s\n",count,link->value,link->key);
            count += 1;
            link = link->next;
        }
    }
}
