#include "Player.hpp"
#include "Pawn.hpp"
#include "Empty.hpp"
#include "Turn.hpp"

#include <iostream>

Player::Player(Board *temp_board) {
    _src_board = temp_board;
    for (int i = 0; i < 8; i++) {
        _figures.push_back(new Empty());
    }
    for (int i = 8; i < 16; i++) {
        _figures.push_back(new Pawn(i, _src_board));
        _src_board->get_element(i).set_figure();
        _src_board->get_element(i).set_player();
    }
    for (int i = 16; i < 64; i++) {
        _figures.push_back(new Empty());
    }
}

void Player::change_pos(direction temp_direction) {
    _src_board->get_element(_position).set_player_off();
    switch (temp_direction) {
        case up:
            _position += 8;
            _position = _position > 63 ? _position - 8 : _position;
            _src_board->get_element(_position).set_player_on();
            return;
        case down:
            _position -= 8;
            _position = _position < 0 ? _position + 8 : _position;
            _src_board->get_element(_position).set_player_on();
            return;
        case left:
            if (_position % 8 != 0) _position--;
            _src_board->get_element(_position).set_player_on();
            return;
        case right:
            if (_position % 8 != 7) _position++;
            _src_board->get_element(_position).set_player_on();
            return;
    }
}

bool Player::path(int index) {
    if (_figures[index]->type() == empty) return false;
    _figures[index]->show_fields();
    return true;
}

void Player::mirror() {
    for (int i = 0; i < 32; i++) {
        std::swap(_figures[i], _figures[63 - (7 - i % 8) - 8 * (i / 8)]);
        _figures[i]->set_index(i);
        _figures[63 - (7 - i % 8) - 8 * (i / 8)]->set_index(63 - (7 - i % 8) - 8 * (i / 8));
        if (first_mirror) {
            if (_figures[i]->type() != empty) {
                _src_board->get_element(i).set_figure();
                _src_board->get_element(i).set_player();
            } else {
                _src_board->get_element(i).destroy_figure();
            }
            if (_figures[63 - (7 - i % 8) - 8 * (i / 8)]->type() != empty) {
                _src_board->get_element(63 - (7 - i % 8) - 8 * (i / 8)).set_figure();
                _src_board->get_element(i).set_player();
            } else {
                _src_board->get_element(63 - (7 - i % 8) - 8 * (i / 8)).destroy_figure();
            }
        } else {
            if (_figures[i]->type() != empty) {
                _src_board->get_element(i).set_figure();
                _src_board->get_element(i).set_player();
            }
            if (_figures[63 - (7 - i % 8) - 8 * (i / 8)]->type() != empty) {
                _src_board->get_element(63 - (7 - i % 8) - 8 * (i / 8)).set_figure();
                _src_board->get_element(i).set_player();
            }
        }
    }
    if (!first_mirror) {
        _figures[63 - (7 - prev_player_pos % 8) - 8 * (prev_player_pos / 8)] = new Empty;
        _position = prev_player_pos;
        _src_board->get_element(_position).set_player_on();
    }
    first_mirror = !first_mirror;
}

void Player::pick() {
    _src_board->get_element(_prev_position).deactivate();
    if (_src_board->get_element(_position).predict_check()) {
        _src_board->get_element(_position).set_player_off();
        _figures[_prev_position]->hide_fields();
        _figures[_prev_position]->transition(_position);
        if (_position != _prev_position) {
            _figures[_position] = _figures[_prev_position];
            _figures[_prev_position] = new Empty();
            _src_board->get_element(_position).set_figure();
            _src_board->get_element(_prev_position).destroy_figure();
        }
        mirror();
        prev_player_pos = _position;
        turn++;
        turn %= 2;
        return;
    }
    _figures[_prev_position]->hide_fields();
    _prev_position = _position;
    if (!path(_position)) return;
    _src_board->get_element(_position).activate();
}

Player::~Player() {
    _figures.clear();
}