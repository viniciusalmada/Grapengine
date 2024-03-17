#ifndef GRAPENGINE_IPUBSUB_HPP
#define GRAPENGINE_IPUBSUB_HPP

#include <list>

namespace GE
{
  template <typename Msg>
  class ISubscriber;

  template <class Msg>
  class IPublisher
  {
  public:
    void Subscribe(Ref<ISubscriber<Msg>> sub) { m_subs.push_back(sub); };
    void Unsubscribe(Ref<ISubscriber<Msg>> sub) { m_subs.remove(sub); };
    virtual void Publish(Msg m) const
    {
      for (const auto& item : m_subs)
        item->OnUpdate(m);
    }

  private:
    std::list<Ref<ISubscriber<Msg>>> m_subs;
  };

  template <class Msg>
  class ISubscriber
  {
  public:
    virtual void OnUpdate(Msg data) = 0;
  };
}
#endif // GRAPENGINE_IPUBSUB_HPP
