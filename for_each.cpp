template <template <typename FRT> typename F, typename it>
requires std::same_as<std::decay_t<F<void>>, std::function<void()>>
auto for_each(it begin, it end, F<int> f) -> decltype(auto) {
    for(; begin != end; begin++) {
        f(*begin);
    }
    return f;
}
