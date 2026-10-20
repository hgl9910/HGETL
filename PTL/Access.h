#pragma once

    /*
    ----------------------------------- 
    field access type
    controls general access to fields
    -------------------------------------
    */
    template<bool r =false, bool w = false>
    struct access {
        static constexpr bool is_readable  = r;
        static constexpr bool is_writeable = w;
    }; 
    
	
    using ro_policy = access<true,false>;
    using wo_policy = access<false,true>;
    using rw_policy = access<true,true>;

    template<typename T>
    concept access_policy = requires(T t) { t.is_readable && t.is_writeable; };


