#ifndef BLOCK_HPP
#define BLOCK_HPP

#define BLOCKWIDTH 16
#define BLOCKHEIGHT 16

class Block {
    public:
        Block();
        void generate();
        void render(char **target);
        ~Block();
    private:
        char data[BLOCKHEIGHT][BLOCKWIDTH];
};

#endif
