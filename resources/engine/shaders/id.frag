#version 450 core

uniform uint u_id;

out uint frag_id;

void main() {
    frag_id = u_id;
}
